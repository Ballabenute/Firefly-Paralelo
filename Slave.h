/*
 * Slave.h
 * Copyright (C) 2018 lopespt <lopespt@UX501VW>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SLAVE_H
#define SLAVE_H
#include "Cluster.h"
#include "bests.h"
#include "tsallis.h"
#include <set>

struct FFData {
  vector<vector<int>> fireflies;
  vector<double> histogram;
  int nthresholds;
};

void receiveData(Cluster &c, FFData &data) {
  int szFireflies;
  c.receive(szFireflies);
  data.fireflies.clear();

  vector<int> temp;
  for (int i = 0; i < szFireflies; i++) {
    c.receive(temp);
    data.fireflies.push_back(temp);
  }

  c.broadcast(data.histogram, 0);
  c.broadcast(data.nthresholds, 0);
}

void receiveData2(Cluster &c, vector<vector<int>> &fireflies) {
  int n;
  c.broadcast(n, 0);
  fireflies.resize(n);

  vector<int> f;
  for (int i = 0; i < n; i++) {
    c.broadcast(f, 0);
    fireflies[i] = f;
  }
}

vector<double> evaluateFireflyes(FFData &data) {
  vector<double> zn;

  for (int h = 0; h < data.fireflies.size(); h++) {
    zn.push_back(psrAvaliacaoTsallis(data.histogram.data(), 0.35,
                                     data.fireflies[h], data.nthresholds) *
                 (-1));
  }
  return zn;
}

vector<vector<double>> calcDists(Cluster &c, vector<vector<int>> ff) {
  vector<vector<double>> dists;
  int n = ff.size();
  int each = n / (c.size() - 1);
  int from = (c.rank() - 1) * each;
  int to = c.rank() * each;

  for (int i = from; i < to; i++) {
    vector<double> line;
    for (int j = 0; j < n; j++) {
      line.push_back(dist(ff[i], ff[j]));
    }
    dists.push_back(line);
  }

  return dists;
}

void sendDists(Cluster &c, vector<vector<double>> &dists) {
  for (auto v : dists) {
    c.send(v, c.rank(), 0);
  }
}

void slave(Cluster &c) {
  int has_more = true;
  while (1) {
    c.broadcast(has_more, 0);
    if (has_more == 0)
      return;

    FFData data;
    receiveData(c, data);
    vector<double> avals = evaluateFireflyes(data);
    c.send(avals, c.rank(), 0);
    vector<vector<int>> ff;
    receiveData2(c, ff);
    vector<vector<double>> dists = calcDists(c, ff);
    sendDists(c, dists);
  };
}

#endif /* !SLAVE_H */
