/*
 * MPI.h
 * Copyright (C) 2018 lopespt <lopespt@UX501VW>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CLUSTER_H
#define CLUSTER_H
#include <mpi.h>

class Cluster {
private:
  MPI_Comm com;
  int _rank;
  int _size;

public:
  Cluster(int *argc, char ***argv) {
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &_size);
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

  Cluster operator=(Cluster &c) = delete;
  Cluster(Cluster &c) = delete;
};

#endif /* !CLUSTER_H */
