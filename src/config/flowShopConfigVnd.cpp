//
// Created by Oscar Jauffret on 01/05/2025.
//

#include "../../include/config/flowShopConfigVnd.hpp"

#include <iostream>

using std::cerr;
using std::endl;
using std::invalid_argument;

FlowShopConfigVND::FlowShopConfigVND(int argc, char* argv[]): FlowShopConfig(argc, argv) {
    // If the algorithm type is VND, the only argument is the VND strategy
    // The third argument is the VND strategy
    if (argc != 4) {
        cerr << "Invalid number of arguments for VND!" << endl;
        throw invalid_argument("Usage: ./pfsp --vnd --instance --tei|--tie");
    }

    string vndArg = argv[3];
    if (vndArg == "--tei") {
        vndStrategy = VNDStrategy::TEI;
    } else if (vndArg == "--tie") {
        vndStrategy = VNDStrategy::TIE;
    } else {
        throw invalid_argument("Invalid VND strategy! Use --tei or --tie.");
    }
}

VNDStrategy FlowShopConfigVND::getVNDStrategy() const {
    return vndStrategy;
}