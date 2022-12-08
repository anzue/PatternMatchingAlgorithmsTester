cmake_minimum_required(VERSION 3.18)
project(PatternMatchingSIMDAMD)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1 -march=native")

include_directories(. main algorithms)

add_executable(PatternMatchingSIMDAMD main/main.cpp
  #      algorithms/developed/bricks26k.cpp
        algorithms/developed/RZk_byte.cpp
        algorithms/developed/RZk_W2_byte.cpp
        algorithms/developed/RZk_W2_MMX.cpp
        algorithms/developed/RZk_W2_pointer.cpp
        algorithms/developed/RZk_W2_SIMD3.cpp
        algorithms/developed/RZk_W3_byte.cpp
        algorithms/developed/RZk_W3_byte_copy.cpp
        algorithms/developed/RZk_W3_pointer.cpp
        algorithms/developed/RZk_W3_SIMD1.cpp
        algorithms/developed/RZk_W3_SIMD2.cpp
        algorithms/developed/RZk_w3_simd2_range_cmp.cpp
        algorithms/developed/RZk_W3_SIMD3.cpp
        algorithms/developed/RZk_W3_SIMD3_range_cmp.cpp
        algorithms/developed/RZk_W4_SIMD2.cpp
        algorithms/developed/RZk_W4_SIMD3.cpp
        algorithms/developed/RZk_W4_SIMD3_pointer.cpp
        algorithms/developed/test_placeholder.cpp
        algorithms/developed/Z8.cpp
        algorithms/developed/Z8_w2.cpp
        algorithms/developed/Zk.cpp
        algorithms/developed/Zk_shift2.cpp
        algorithms/developed/Zk_w2.cpp
        algorithms/imported/include/AUTOMATON.cpp
        algorithms/imported/include/AUTOMATON.h
        algorithms/imported/include/define.h
        algorithms/imported/include/GRAPH.h
        algorithms/imported/include/log2.h
        algorithms/imported/include/main.h
        algorithms/imported/include/stats.h
        algorithms/imported/include/timer.h
        algorithms/imported/ac.cpp
        algorithms/imported/ag.cpp
        algorithms/imported/akc.cpp
        algorithms/imported/aoso2.cpp
        algorithms/imported/aoso4.cpp
        algorithms/imported/aoso6.cpp
        algorithms/imported/askip.cpp
        algorithms/imported/aut.cpp
        algorithms/imported/bf.cpp
        algorithms/imported/bfs.cpp
        algorithms/imported/blim.cpp
        algorithms/imported/bm.cpp
        algorithms/imported/bmh-sbndm.cpp
        algorithms/imported/bndm.cpp
        algorithms/imported/bndml.cpp
        algorithms/imported/bndmq2.cpp
        algorithms/imported/bndmq4.cpp
        algorithms/imported/bndmq6.cpp
        algorithms/imported/bom.cpp
        algorithms/imported/bom2.cpp
        algorithms/imported/br.cpp
        algorithms/imported/bsdm.cpp
        algorithms/imported/bsdm2.cpp
        algorithms/imported/bsdm3.cpp
        algorithms/imported/bsdm4.cpp
        algorithms/imported/bsdm5.cpp
        algorithms/imported/bsdm6.cpp
        algorithms/imported/bsdm7.cpp
        algorithms/imported/bsdm8.cpp
        algorithms/imported/bww.cpp
        algorithms/imported/bxs.cpp
        algorithms/imported/bxs1.cpp
        algorithms/imported/bxs2.cpp
        algorithms/imported/bxs3.cpp
        algorithms/imported/bxs4.cpp
        algorithms/imported/bxs6.cpp
        algorithms/imported/bxs8.cpp
        algorithms/imported/dbww.cpp
        algorithms/imported/dbww2.cpp
        algorithms/imported/ebom.cpp
      #  algorithms/imported/epsm.cpp
        algorithms/imported/faoso2.cpp
        algorithms/imported/faoso4.cpp
        algorithms/imported/faoso6.cpp
        algorithms/imported/fbom.cpp
        algorithms/imported/fdm.cpp
        algorithms/imported/ffs.cpp
        algorithms/imported/fjs.cpp
        algorithms/imported/fndm.cpp
        algorithms/imported/fs-w1.cpp
        algorithms/imported/fs-w2.cpp
        algorithms/imported/fs-w4.cpp
        algorithms/imported/fs-w6.cpp
        algorithms/imported/fs-w8.cpp
        algorithms/imported/fs.cpp
        algorithms/imported/fsbndm-w1.cpp
        algorithms/imported/fsbndm-w2.cpp
        algorithms/imported/fsbndm-w4.cpp
        algorithms/imported/fsbndm-w6.cpp
        algorithms/imported/fsbndm-w8.cpp
        algorithms/imported/fsbndm.cpp
        algorithms/imported/fsbndmq20.cpp
        algorithms/imported/fsbndmq21.cpp
        algorithms/imported/fsbndmq31.cpp
        algorithms/imported/fsbndmq32.cpp
        algorithms/imported/fsbndmq41.cpp
        algorithms/imported/fsbndmq42.cpp
        algorithms/imported/fsbndmq43.cpp
        algorithms/imported/fsbndmq61.cpp
        algorithms/imported/fsbndmq62.cpp
        algorithms/imported/fsbndmq64.cpp
        algorithms/imported/fsbndmq81.cpp
        algorithms/imported/fsbndmq82.cpp
        algorithms/imported/fsbndmq84.cpp
        algorithms/imported/fsbndmq86.cpp
        algorithms/imported/graspm.cpp
        algorithms/imported/hash3.cpp
        algorithms/imported/hash5.cpp
        algorithms/imported/hash8.cpp
        algorithms/imported/hor.cpp
        algorithms/imported/horspool.cpp
        algorithms/imported/ildm1.cpp
        algorithms/imported/ildm2.cpp
        algorithms/imported/kbndm.cpp
        algorithms/imported/kmp.cpp
        algorithms/imported/kmpskip.cpp
        algorithms/imported/kr.cpp
        algorithms/imported/ksa.cpp
        algorithms/imported/lbndm.cpp
   #     algorithms/imported/ldm.cpp
        algorithms/imported/mp.cpp
   #     algorithms/imported/ms.cpp
        algorithms/imported/nsn.cpp
   #     algorithms/imported/om.cpp
        algorithms/imported/pbmh.cpp
        algorithms/imported/qf23.cpp
        algorithms/imported/qf24.cpp
        algorithms/imported/qf26.cpp
        algorithms/imported/qf28.cpp
        algorithms/imported/qf33.cpp
        algorithms/imported/qf34.cpp
        algorithms/imported/qf36.cpp
        algorithms/imported/qf42.cpp
        algorithms/imported/qf43.cpp
        algorithms/imported/qf44.cpp
        algorithms/imported/qf62.cpp
        algorithms/imported/qf63.cpp
        algorithms/imported/qs.cpp
        algorithms/imported/raita.cpp
        algorithms/imported/rcolussi.cpp
        algorithms/imported/rf.cpp
        algorithms/imported/sa.cpp
        algorithms/imported/sabp.cpp
        algorithms/imported/sbndm-bmh.cpp
        algorithms/imported/sbndm-w2.cpp
        algorithms/imported/sbndm-w4.cpp
        algorithms/imported/sbndm-w6.cpp
        algorithms/imported/sbndm.cpp
        algorithms/imported/sbndm2.cpp
        algorithms/imported/sbndmq2.cpp
        algorithms/imported/sbndmq4.cpp
        algorithms/imported/sbndmq6.cpp
        algorithms/imported/sbndmq8.cpp
        algorithms/imported/sfbom.cpp
        algorithms/imported/simon.cpp
        algorithms/imported/skip.cpp
        algorithms/imported/smith.cpp
        algorithms/imported/smoa.cpp
        algorithms/imported/so.cpp
        algorithms/imported/ssabs.cpp
   #     algorithms/imported/ssecp.cpp
   #     algorithms/imported/ssef.cpp
        algorithms/imported/svm0.cpp
        algorithms/imported/svm1.cpp
        algorithms/imported/svm2.cpp
        algorithms/imported/svm3.cpp
        algorithms/imported/svm4.cpp
        algorithms/imported/tbm.cpp
        algorithms/imported/tndm.cpp
        algorithms/imported/tndma.cpp
        algorithms/imported/trf.cpp
        algorithms/imported/ts.cpp
        algorithms/imported/tsw.cpp
        algorithms/imported/tunedbm.cpp
        algorithms/imported/tvsbs-w2.cpp
        algorithms/imported/tvsbs-w4.cpp
        algorithms/imported/tvsbs-w6.cpp
        algorithms/imported/tvsbs-w8.cpp
        algorithms/imported/tvsbs.cpp
        algorithms/imported/tw.cpp
        algorithms/imported/ufndmq2.cpp
        algorithms/imported/ufndmq4.cpp
        algorithms/imported/ufndmq6.cpp
        algorithms/imported/ufndmq8.cpp
        algorithms/imported/zt.cpp
        algorithms/simd_defines_i128.h
        algorithms/simd_defines_i64.h
        algorithms/algos.h
        algorithms/consts.h
        algorithms/consts.cpp
        algorithms/executablealgo.cpp
        algorithms/executablealgo.h
        main/main.cpp
        main/test.cpp
        main/test.h
        main/algoexecutor.h
      #  algorithms/developed/bricks26k.cpp algorithms/developed/bricks43.cpp algorithms/consts.cpp algorithms/algoexecutor.cpp algorithms/algoexecutor.h
      )
