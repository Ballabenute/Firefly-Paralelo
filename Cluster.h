/*
 * MPI.h
 * Copyright (C) 2018 lopespt <lopespt@UX501VW>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MPI_H
#define MPI_H
#include <mpi.h>
#include <vector>
using namespace std;

class Cluster {
private:
  MPI_Comm com;
  int _rank;
  int _size;
  bool _running;

public:
  Cluster(int *argc, char ***argv) {
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &_size);
    _running = true;
  }
  ~Cluster() {
    MPI_Finalize();
  }
  int rank() const {
    return _rank;
  }
  int size() const {
    return _size;
  }

  void send(int &send, int from, int to) {
    if (rank() == from) {
      MPI_Send(&send, 1, MPI_INT, to, 3, MPI_COMM_WORLD);
    }
  }
  int receive(int &receive, int from = MPI_ANY_SOURCE) {
    MPI_Status s;
    MPI_Recv(&receive, 1, MPI_INT, from, 3, MPI_COMM_WORLD, &s);
    return s.MPI_SOURCE;
  }

  void send(vector<int> &send, int from, int to) {
    if (rank() == from) {
      int sz = send.size();
      MPI_Send(&sz, 1, MPI_INT, to, 1, MPI_COMM_WORLD);
      MPI_Send(send.data(), send.size(), MPI_INT, to, 2, MPI_COMM_WORLD);
    }
  }

  int receive(vector<int> &receive, int from = MPI_ANY_SOURCE) {
    MPI_Status s;
    int n;
    MPI_Recv(&n, 1, MPI_INT, from, 1, MPI_COMM_WORLD, &s);
    receive.resize(n);
    MPI_Recv(receive.data(), n, MPI_INT, s.MPI_SOURCE, 2, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    return s.MPI_SOURCE;
  }

  void send(vector<double> &send, int from, int to) {
    if (rank() == from) {
      int sz = send.size();
      MPI_Send(&sz, 1, MPI_INT, to, 1, MPI_COMM_WORLD);
      MPI_Send(send.data(), send.size(), MPI_DOUBLE, to, 2, MPI_COMM_WORLD);
    }
  }

  int receive(vector<double> &receive, int from = MPI_ANY_SOURCE) {
    MPI_Status s;
    int n;
    MPI_Recv(&n, 1, MPI_INT, from, 1, MPI_COMM_WORLD, &s);
    receive.resize(n);
    MPI_Recv(receive.data(), n, MPI_DOUBLE, s.MPI_SOURCE, 2, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    return s.MPI_SOURCE;
  }

  void broadcast(vector<int> &sendReceive, int from) {
    if (rank() == from) {
      int sz = sendReceive.size();
      MPI_Bcast(&sz, 1, MPI_INT, from, MPI_COMM_WORLD);
      MPI_Bcast(sendReceive.data(), sendReceive.size(), MPI_INT, from,
                MPI_COMM_WORLD);
    } else {
      int sz;
      MPI_Bcast(&sz, 1, MPI_INT, from, MPI_COMM_WORLD);
      sendReceive.resize(sz);
      MPI_Bcast(sendReceive.data(), sendReceive.size(), MPI_INT, from,
                MPI_COMM_WORLD);
    }
  }
  void broadcast(vector<double> &sendReceive, int from) {
    if (rank() == from) {
      int sz = sendReceive.size();
      MPI_Bcast(&sz, 1, MPI_INT, from, MPI_COMM_WORLD);
      MPI_Bcast(sendReceive.data(), sendReceive.size(), MPI_DOUBLE, from,
                MPI_COMM_WORLD);
    } else {
      int sz;
      MPI_Bcast(&sz, 1, MPI_INT, from, MPI_COMM_WORLD);
      sendReceive.resize(sz);
      MPI_Bcast(sendReceive.data(), sendReceive.size(), MPI_DOUBLE, from,
                MPI_COMM_WORLD);
    }
  }
  void broadcast(int &sendReceive, int from) {
    MPI_Bcast(&sendReceive, 1, MPI_DOUBLE, from, MPI_COMM_WORLD);
  }

  Cluster operator=(Cluster &c) = delete;
  Cluster(Cluster &c) = delete;

  bool is_running() const {
    return _running;
  }

  void stop() {
    _running = false;
  }
};

#endif /* !MPI_H */
