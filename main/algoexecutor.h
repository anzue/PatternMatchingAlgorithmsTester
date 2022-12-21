#pragma once

#include "../algorithms/executablealgo.h"

inline vector<Algo *> get_algos()
{
  return {
      new KExecutableAlgo("test_algo_{}", test_algo, 14, false),
      new KExecutableAlgo("RZ{}_w2_simd3", RZk_w2_simd3, 14, false),
      new KExecutableAlgo("RZ{}_w3_byte", RZk_w3_byte, 14, true),
      new KExecutableAlgo("RZ{}_w3_simd2", RZk_w3_simd2, 14, false),
      new KExecutableAlgo("RZ{}_w4_simd2", RZk_w4_simd2, 14, false),

      new KExecutableAlgo("RZ{}_w4_simd3", RZk_w4_simd3, 14, false),

      //       new KExecutableAlgo("RZ{}_w3_byte", RZk_w3_byte, 14, false),

      //  new ExecutableAlgo("Bricks43", Bricks43, true, {2, 15}, {2, 1000}),
      //  new KExecutableAlgo("RZ{}_w2_pointer", RZk_w2_pointer, 13, true),
      //    new KExecutableAlgo("RZ{}_w2_pointer", RZk_w2_pointer, 14, false),
      //           new KExecutableAlgo("RZ{}_w3_simd2", RZk_w3_simd2, 13, false),

      /*
                new KExecutableAlgo("RZ{}_byte", RZk_byte, 13, false),
                 new KExecutableAlgo("RZ{}_byte", RZk_byte, 14, false),

                 new KExecutableAlgo("RZ{}_w2_byte", RZk_w2_byte, 13, false),
                 new KExecutableAlgo("RZ{}_w2_byte", RZk_w2_byte, 14, false),



                 new KExecutableAlgo("RZ{}_w2_simd3", RZk_w2_simd3, 13, false),



                 new KExecutableAlgo("RZ{}_w3_pointer", RZk_w3_pointer, 13, true),
                 new KExecutableAlgo("RZ{}_w3_pointer", RZk_w3_pointer, 14, false),

                 new KExecutableAlgo("RZ{}_w3_simd1", RZk_w3_simd1, 13, false),
                 new KExecutableAlgo("RZ{}_w3_simd1", RZk_w3_simd1, 14, false),

                 new KExecutableAlgo("RZ{}_w3_simd2", RZk_w3_simd2, 13, false),
                 new KExecutableAlgo("RZ{}_w3_simd2", RZk_w3_simd2, 14, false),

                 new KExecutableAlgo("RZ{}_w3_simd3", RZk_w3_simd3, 13, false),

                 new KExecutableAlgo("RZ{}_w3_simd2_range_cmp", RZk_w3_simd2_range_cmp, 13, false),

                 new KExecutableAlgo("RZ{}_w3_simd3_range_cmp", RZk_w3_simd3_range_cmp, 13, false),

                 new KExecutableAlgo("RZ{}_w4_simd2", RZk_w4_simd2, 13, false),

                 new KExecutableAlgo("RZ{}_w4_simd3", RZk_w4_simd3, 13, false),
                 new KExecutableAlgo("RZ{}_w4_simd3_pointer", RZk_w4_simd3_pointer, 13, false),

                 //  new KExecutableAlgo("test_algo_{}", test_algo, 14, false),

                 //   new ExecutableAlgo("FSBNDM_W1", fsbndm_w1, false),
                 //   new ExecutableAlgo("FSBNDM_W2", fsbndm_w2, false),
                 new ExecutableAlgo("FSBNDM_W4", fsbndm_w4, false),
                 new ExecutableAlgo("FSBNDM_W6", fsbndm_w6, false),
                 new ExecutableAlgo("FSBNDM_W8", fsbndm_w8, false),
                 new ExecutableAlgo("FSBNDM_31", fsbndmq31, false),

                 new ExecutableAlgo("FS", fs, false),
                 new ExecutableAlgo("FSw4", fs_w4, false),
                 new ExecutableAlgo("FSw6", fs_w6, false),
                 new ExecutableAlgo("FSw8", fs_w8, false),
                 new ExecutableAlgo("FJS", fjs, false),

                 new KExecutableAlgo("Z{}_byte", Zk_byte, 13, true),
                 new KExecutableAlgo("Z{}_byte", Zk_byte, 14, false),

                 new KExecutableAlgo("Z{}_w2_byte", Zk_w2_byte, 13, true),
                 new KExecutableAlgo("Z{}_w2_byte", Zk_w2_byte, 14, false),

                 new ExecutableAlgo("Z8", Z8_byte, false), */

  };
}
