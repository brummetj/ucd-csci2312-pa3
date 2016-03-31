//
//  Kmeans.cpp
//  PA3 Intermediate
//
//  Created by Joshua Brummet on 3/27/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include <cassert>

#include "KMeans.h"
#include "Exceptions.h"


namespace Clustering {
    
    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) {

        //Couldn't get past errored out stream... No need for Kmeans!

    }
    
    
    KMeans::~KMeans()
    {


    }

    unsigned int KMeans::getMaxIter()
    {
        return __maxIter;
    }
    unsigned int KMeans::getNumIters()
    {
        return __numIter;
    }
    unsigned int KMeans::getNumNonemptyClusters()
    {
        return __numNonempty;
    }
    unsigned int KMeans::getNumMovesLastIter()
    {
        return __numMovesLastIter;
    }
    

    Cluster &KMeans::operator[](unsigned int u) {
        return *(__clusters[u]);
    }
    const Cluster &KMeans::operator[](unsigned int u) const {
        return *(__clusters[u]);
    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans)
    {
        
        return os;
    }

    void KMeans::run() {
    }
}
