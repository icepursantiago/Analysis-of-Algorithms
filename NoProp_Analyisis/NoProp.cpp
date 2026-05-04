// main.cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <Eigen/Dense>
#include "data_loader.h" // Assumes a header for loading/preprocessing data
#include "models.h"       // Assumes a header for MLP classes

// --- Utility Functions ---

// Function to print results in a formatted table
void print_results(const std::vector<Result>& results) {
    std::cout << "\n--- Experimental Results ---\n";
    printf("%-15s | %-15s | %-15s | %-20s | %-20s\n", "Hidden Width", "No-Prop Acc.", "BP Acc.", "No-Prop Time (s)", "BP Time (s)");
    printf("----------------|-----------------|-----------------|----------------------|----------------------\n");
    for (const auto& res : results) {
        printf("%-15d | %-15.4f | %-15.4f | %-20.4f | %-20.4f\n",
               res.hidden_width, res.noprop_acc, res.bp_acc, res.noprop_time, res.bp_time);
    }
}

// Function to calculate accuracy
double calculate_accuracy(const Eigen::MatrixXd& y_pred, const Eigen::MatrixXd& y_true) {
    int correct_predictions = 0;
    for (int i = 0; i < y_true.rows(); ++i) {
        if ((y_pred(i, 0) > 0.5 && y_true(i, 0) == 1) || (y_pred(i, 0) <= 0.5 && y_true(i, 0) == 0)) {
            correct_predictions++;
        }
    }
    return static_cast<double>(correct_predictions) / y_true.rows();
}


// --- Main Execution Logic ---
int main() {
    // --- 1. Load and Prepare Data ---
    std::string filepath = "HTML_Top13_Features.csv";
    Dataset data = load_and_preprocess_data(filepath);

    // --- 2. Define Experimental Setup ---
    std::vector<int> hidden_widths = {16, 32, 64, 128, 256};
    int input_dim = data.X_train.cols();
    int output_dim = 1;
    int epochs = 50;
    double learning_rate_noprop = 0.001;
    double learning_rate_bp = 0.01;

    std::vector<Result> results;

    // --- 3. Run Experiments ---
    for (int width : hidden_widths) {
        std::cout << "\n--- Training with Hidden Width: " << width << " ---\n";
        Result res;
        res.hidden_width = width;

        // --- Classical No-Prop ---
        NoPropMLP noprop_model(input_dim, width, output_dim, learning_rate_noprop);
        auto start_noprop = std::chrono::high_resolution_clock::now();
        noprop_model.train(data.X_train, data.y_train, epochs);
        auto end_noprop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_noprop = end_noprop - start_noprop;
        res.noprop_time = duration_noprop.count();

        Eigen::MatrixXd y_pred_noprop_test = noprop_model.predict_prob(data.X_test);
        res.noprop_acc = calculate_accuracy(y_pred_noprop_test, data.y_test);
        std::cout << "No-Prop Training Time: " << res.noprop_time << "s, Test Accuracy: " << res.noprop_acc << std::endl;


        // --- Backpropagation ---
        BackpropMLP bp_model(input_dim, width, output_dim, learning_rate_bp);
        auto start_bp = std::chrono::high_resolution_clock::now();
        bp_model.train(data.X_train, data.y_train, epochs);
        auto end_bp = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_bp = end_bp - start_bp;
        res.bp_time = duration_bp.count();

        Eigen::MatrixXd y_pred_bp_test = bp_model.predict_prob(data.X_test);
        res.bp_acc = calculate_accuracy(y_pred_bp_test, data.y_test);
        std::cout << "Backprop Training Time: " << res.bp_time << "s, Test Accuracy: " << res.bp_acc << std::endl;

        results.push_back(res);
    }

    // --- 4. Print Final Results Summary ---
    print_results(results);

    return 0;
}

// models.h
#ifndef MODELS_H
#define MODELS_H

#include <Eigen/Dense>
#include <iostream>
#include <vector>

// Structure to hold experiment results
struct Result {
    int hidden_width;
    double noprop_acc;
    double bp_acc;
    double noprop_time;
    double bp_time;
};


// --- Activation Functions ---
Eigen::MatrixXd relu(const Eigen::MatrixXd& x) {
    return x.cwiseMax(0);
}

Eigen::MatrixXd relu_derivative(const Eigen::MatrixXd& x) {
    return (x.array() > 0).cast<double>().matrix();
}

Eigen::MatrixXd sigmoid(const Eigen::MatrixXd& x) {
    return 1.0 / (1.0 + (-x.array()).exp());
}

// --- Classical No-Prop MLP ---
class NoPropMLP {
public:
    NoPropMLP(int input_dim, int hidden_dim, int output_dim, double lr)
        : input_dim_(input_dim), hidden_dim_(hidden_dim), output_dim_(output_dim), lr_(lr) {
        // Xavier initialization for frozen hidden layer
        double stddev1 = sqrt(1.0 / input_dim_);
        W1_ = Eigen::MatrixXd::Random(input_dim_, hidden_dim_) * stddev1;
        b1_ = Eigen::MatrixXd::Zero(1, hidden_dim_);

        // Xavier initialization for trainable output layer
        double stddev2 = sqrt(1.0 / hidden_dim_);
        W2_ = Eigen::MatrixXd::Random(hidden_dim_, output_dim_) * stddev2;
        b2_ = Eigen::MatrixXd::Zero(1, output_dim_);
    }

    Eigen::MatrixXd forward(const Eigen::MatrixXd& X) {
        Eigen::MatrixXd Z1 = X * W1_ + b1_.replicate(X.rows(), 1);
        Eigen::MatrixXd H = relu(Z1);
        Eigen::MatrixXd Y_hat = H * W2_ + b2_.replicate(H.rows(), 1);
        return Y_hat;
    }

    Eigen::MatrixXd predict_prob(const Eigen::MatrixXd& X) {
         return sigmoid(forward(X));
    }

    void train(const Eigen::MatrixXd& X_train, const Eigen::MatrixXd& y_train, int epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (int i = 0; i < X_train.rows(); ++i) {
                Eigen::MatrixXd x = X_train.row(i);
                Eigen::MatrixXd y = y_train.row(i);

                // Forward pass to get hidden activations and final output
                Eigen::MatrixXd Z1 = x * W1_ + b1_;
                Eigen::MatrixXd H = relu(Z1);
                Eigen::MatrixXd Y_hat = H * W2_ + b2_;

                // Compute error (target - prediction)
                Eigen::MatrixXd error = y - Y_hat;

                // Update only output layer weights (LMS rule)
                W2_ += lr_ * (H.transpose() * error);
                b2_ += lr_ * error;
            }
        }
    }

private:
    int input_dim_, hidden_dim_, output_dim_;
    double lr_;
    Eigen::MatrixXd W1_, b1_; // Frozen hidden layer
    Eigen::MatrixXd W2_, b2_; // Trainable output layer
};


// --- Backpropagation MLP ---
class BackpropMLP {
public:
    BackpropMLP(int input_dim, int hidden_dim, int output_dim, double lr)
        : input_dim_(input_dim), hidden_dim_(hidden_dim), output_dim_(output_dim), lr_(lr) {
        double stddev1 = sqrt(1.0 / input_dim_);
        W1_ = Eigen::MatrixXd::Random(input_dim_, hidden_dim_) * stddev1;
        b1_ = Eigen::MatrixXd::Zero(1, hidden_dim_);

        double stddev2 = sqrt(1.0 / hidden_dim_);
        W2_ = Eigen::MatrixXd::Random(hidden_dim_, output_dim_) * stddev2;
        b2_ = Eigen::MatrixXd::Zero(1, output_dim_);
    }
    
    Eigen::MatrixXd predict_prob(const Eigen::MatrixXd& X) {
        Eigen::MatrixXd Z1 = X * W1_ + b1_.replicate(X.rows(), 1);
        Eigen::MatrixXd H = relu(Z1);
        Eigen::MatrixXd Z2 = H * W2_ + b2_.replicate(H.rows(), 1);
        return sigmoid(Z2);
    }

    void train(const Eigen::MatrixXd& X_train, const Eigen::MatrixXd& y_train, int epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (int i = 0; i < X_train.rows(); ++i) {
                Eigen::MatrixXd x = X_train.row(i);
                Eigen::MatrixXd y = y_train.row(i);

                // Forward Pass
                Eigen::MatrixXd Z1 = x * W1_ + b1_;
                Eigen::MatrixXd H = relu(Z1);
                Eigen::MatrixXd Z2 = H * W2_ + b2_;
                Eigen::MatrixXd Y_hat = sigmoid(Z2);

                // Backward Pass (Gradient Calculation)
                Eigen::MatrixXd error = y - Y_hat;
                Eigen::MatrixXd d_output = error.array() * (Y_hat.array() * (1 - Y_hat.array()));

                Eigen::MatrixXd error_hidden = d_output * W2_.transpose();
                Eigen::MatrixXd d_hidden = error_hidden.array() * relu_derivative(Z1).array();

                // Weight Updates
                W2_ += lr_ * (H.transpose() * d_output);
                b2_ += lr_ * d_output;
                W1_ += lr_ * (x.transpose() * d_hidden);
                b1_ += lr_ * d_hidden;
            }
        }
    }

private:
    int input_dim_, hidden_dim_, output_dim_;
    double lr_;
    Eigen::MatrixXd W1_, b1_, W2_, b2_;
};

#endif // MODELS_H
