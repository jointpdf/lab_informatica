#include "sir_model.hpp"

//Constructor
SIRModel::SIRModel(SIR sir_zero, float beta, float gamma, unsigned int days)
    : beta_(beta), gamma_(gamma), days_(days) {
    N_ = sir_zero.S + sir_zero.I + sir_zero.R;
    record_.push_back(sir_zero);
}

//Check method implementation
void SIRModel::check() {
    if (typeid(beta_) != typeid(float) || typeid(gamma_) != typeid(float) ||
        beta_ < 0 || beta_ > 1 || gamma_ < 0 || gamma_ > 1){
        throw std::runtime_error{"beta and gamma must be between zero and one"};
    }

    if (round(record_[0].S) != record_[0].S || round(record_[0].I) != record_[0].I || round(record_[0].R) != record_[0].R || record_[0].S < 0 ||
        record_[0].I < 0 || record_[0].R < 0) {
        throw std::runtime_error{"S, I e R must be non-negative integer"};
    }

    if (typeid(days_) != typeid(unsigned int)) {
        throw std::runtime_error{"number of days must be non-negative integer"};
    }
}

//Dinamic method implementation
void SIRModel::dinamic() {
    for (unsigned int j = 0; j < days_; j++) {
        SIR last = record_.back();
        SIR next;
        next.S = last.S - (beta_ * last.S * last.I / N_);
        next.I = last.I + (beta_ * last.S * last.I / N_) - (gamma_ * last.I);
        next.R = last.R + (gamma_ * last.I);
        record_.push_back(next);
    }
    
}

//Approx method implementation
void SIRModel::approx(){
    for (std::size_t i = 0; i < record_.size(); i++) {
        if (round(record_[i].S) + round(record_[i].I + round(record_[i].R)) == round(N_)) {
            record_[i].S = round(record_[i].S);
            record_[i].I = round(record_[i].I);
            record_[i].R = round(record_[i].R);
        }
        else if (round(record_[i].S) + round(record_[i].I) + round(record_[i].R) > round(N_)) {
            if (std::min_element(&record_[i].S, &record_[i].R + 1) == &record_[i].S){
                record_[i].S = round(record_[i].S - 0.5);
                record_[i].I = round(record_[i].I);
                record_[i].R = round(record_[i].R);
            }
            else if (std::min_element(&record_[i].S, &record_[i].R + 1) == &record_[i].I){
                record_[i].S = round(record_[i].S);
                record_[i].I = round(record_[i].I - 0.5);
                record_[i].R = round(record_[i].R);
            }
            else {
                record_[i].S = round(record_[i].S);
                record_[i].I = round(record_[i].I);
                record_[i].R = round(record_[i].R - 0.5);
            }
        }
        else if (round(record_[i].S) + round(record_[i].I + round(record_[i].R)) < round(N_)){
            if (std::max_element(&record_[i].S, &record_[i].R + 1) == &record_[i].S){
                record_[i].S = round(record_[i].S + 0.5);
                record_[i].I = round(record_[i].I);
                record_[i].R = round(record_[i].R);
            }
            else if (std::max_element(&record_[i].S, &record_[i].R + 1) == &record_[i].I){
                record_[i].S = round(record_[i].S);
                record_[i].I = round(record_[i].I + 0.5);
                record_[i].R = round(record_[i].R);
            }
            else {
                record_[i].S = round(record_[i].S);
                record_[i].I = round(record_[i].I);
                record_[i].R = round(record_[i].R + 0.5);
            }
        }
    }
}
//Print method implementation
void SIRModel::print() {
    std::cout << "      ||####### S ###||### I ###||### R #######||\n";
    for (std::size_t i = 0; i < record_.size(); i++) {
        std::cout << "d_" << i << "           " << round(record_[i].S)
        << "         " << round(record_[i].I) << "          "
        << round(record_[i].R) << std::endl;
    }
}   