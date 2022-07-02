* **Date : 2022-06-30**
* **Last Modified At : 2022-06-30**

<!-- TOC -->

- [Introduction to CUDA](#introduction-to-cuda)
    - [What is CUDA?](#what-is-cuda)
    - [Why use GPU?](#why-use-gpu)
    - [Prerequisites](#prerequisites)
        - [Terminology](#terminology)
        - [Workflow](#workflow)
        - [Hello World](#hello-world)
        - [Hierarchy of threads](#hierarchy-of-threads)
        - [Inbuilt variables](#inbuilt-variables)
        - [Components of GPU](#components-of-gpu)
        - [pros](#pros)
        - [cons](#cons)
    - [Reference](#reference)
- [Dive into basics of GPU, CUDA & Accelerated programming using Numba in Python](#dive-into-basics-of-gpu-cuda--accelerated-programming-using-numba-in-python)
        - [Brief intro to Numba](#brief-intro-to-numba)
        - [What is CUDA & why use it?](#what-is-cuda--why-use-it)
            - [What are CUDA cores?](#what-are-cuda-cores)
            - [Why do we use CUDA?](#why-do-we-use-cuda)
        - [CUDA Kernels](#cuda-kernels)
        - [Threads, Blocks, Grid and Wrap in CUDA](#threads-blocks-grid-and-wrap-in-cuda)
        - [Streaming Multiprocessors](#streaming-multiprocessors)
        - [SMIT Architecture](#smit-architecture)
        - [Coalesced Memory Access](#coalesced-memory-access)
        - [Bank conflicts](#bank-conflicts)
        - [Numba on CPU and GPU](#numba-on-cpu-and-gpu)
            - [On CPU](#on-cpu)
            - [On GPU](#on-gpu)
        - [Conclusion](#conclusion)
        - [Reference](#reference)

<!-- /TOC -->



# Introduction to CUDA

GPU programming using CUDA

<img src = 'https://miro.medium.com/max/542/1*Z_vXwV0SPudOAdlZnoAkWA.png'>


## What is CUDA?

CUDA는 Compute Unified Device Architecture을 의미한다. CUDA는 범용 프로그램(general purpose program)용 GPU를 노출하는 Nvidia의 이기종 프로그래밍 언어(heterogeneous programming language)이다. 이기종 프로그래밍(Heterogeneous programming)은 코드가 호스트(CPU)와 장치(Nvidia GPU 장치)라는 2가지 다른 플랫폼에서 실행됨을 의미한다.



## Why use GPU?

CPU는 매우 강력하며 병렬로 실행되는 직렬작업이 거의 없는 저지연 작업(low latency operation)에 더 좋다. 그러나 대규모 병렬 처리가 필요한 코드를 실행해야 하는 경우, CPU의 스레드가 무겁고 운영체제가 context switching이라는 다중처리(multiprocessing)를 구현하기 위해 스레드를 켜고 끄기 때문에 CPU가 실행할 수 있기 때문에 실행하는 데 시간이 더 오래 걸린다. 즉, 느리고 비용이 많이 드는 프로세스이다.

GPU는 CPU에 비해 기하급수적으로 높은 연산처리량(computational throughput)과 대역폭(bandwidth)을 갖고 있다. GPU는 병렬 데이터 처리(parallel data processing)에 더 좋다. 많은 양의 데이터에 대한 부동소수점 산술(floating point arithmetic)과 같은 작은 연산을 수행하는데 더 좋다. 프로그래밍의 미래는 병렬처리이며 GPU는 이를 달성하는 가장 좋은 방법이다.



## Prerequisites

* ```Nvidia Graphics Card```
* ```CUDA toolkit```(https://developer.nvidia.com/cuda-downloads)



### Terminology

시작하기 전에 CUDA 커뮤니티에서 활발히 사용되는 전문용어(jargon)를 이해하는 것이 중요하다.

* `Host` : 호스트는 시스템에서 사용할 수 있는 CPU이다. 호스트와 관련된 시스템 메모리(D RAM)을 `Host memory`라고 한다.
* `Device` : Device는 GPU이고, GPU 메모리라고 `device memory`로 불린다.
* `Kernel` : 커널은 단일 스레드(single thread)에 의해 GPU에서 실행되는 함수이다.
* `Kernel launch` : GPU에 병렬로 코드를 실행하도록 지시하는 CPU이다.
* `Execution Configuration` : GPU에서 실행되는 스레드의 수와 그것을 정의하는 방법
* `CUDA cores` : 부동 소수점 맵(floating point map)을 수행할 수 있는 Nvidia 그래픽 카드의 부동 소수점 단위(floating point unit)이다.



### Workflow

호스트가 실행(execution)을 제어한다. 프로그램은 커널에 도달할 때까지 순차적으로 로드된다. 호스트가 커널 시작을 수행한다. 그것은 다른 커널에 도달한다.

* `host-to-device transfer` : 메모리는 `cudaMalloc`을 사용하여 device memory에 할당된다. host memory의 데이터는 `cudaMemcpy`를 사용하여 device로 복사된다. 장치와 호스트의 통신은 PCI bus를 통해 이루어진다.
* `kernal-load` : GPU 프로그램을 로드하고 실행하여 성능을 위해 chip 위의 데이터를 caching한다.
* `device-to-host transfer` : `cudaMemcpy`를 사용하여 device memory에서 host memory로 결과를 복사한다. `cudaFree`를 사용하여 device memory에서 메모리를 지운다.

장치가 커널 코드를 실행하는 동안, 호스트는 다른 커널 코드나 호스트 코드의 끝에 도달할 때까지, 코드의 다음줄을 계속 진행한다.



### Hello World

Hello World로 시작하는 오랜 전통을 따르자. 다음은 CUDA에서 가장 기본적인 프로그램이다.

``` C
// Program : hello_world.cu
#include <stdio.h>
#include <cuda.h>


__global__ void hello_world() {
    printf("Hello, World\n");
}

int main() {
    hello_world<<<1,1>>>();
    cudaDeviceSynchronize();
    return 0;
}
```

* `__global__` : 는 함수가 device(GPU)에서 실행되고 host(CPU)로부터 호출됨을 나타낸다. 그것은 kernel code를 정의한다.
* `hello_world<<<1,1>>()` : `<<<M,T>>>`는 kernel launch를 의미한다. `__global__`를 가진 코드에 대해 호출되어야 한다. kernel은 `M`개의 thread blocks로 구성된 하나의 grid와 함께 시작된다. 각각의 thread block은 `T` 개의 parallel threads를 갖는다.
* `cudaDeviceSynchronize()` : cuda 코드는 비동기식(asynchronously)으로 실행되고, 호스트는 장치가 실행을 완료할 때까지 항상 기다리지 않을 수도 있다. `cudaDeviceSyncronize`는 장치가 실행을 완료할 때까지 기다린다.

이제 코드를 컴파일해야 한다.

```
$ nvcc -o hello helloworld.cu
```

NVIDIA 컴파일러는 device code와 host code를 분리한다. device code: hello_world는 NVIDIA 컴파일러로 컴파일되고, main function은 gcc를 사용하여 컴파일된다.

프로그램은 간단한 hello world를 출력한다. cuda의 전체 기능을 보여주지 않는다. 왜냐하면 여기서는 오직 하나의 thread만이 hello world를 실행하기 때문이다. 하지만 그 전에 이론을 조금 더 배우도록 하자.



### Hierarchy of threads

cuda에는 스레드의 3개의 계층이 있다.

* `Threads` : 스레드는 cuda core 중 하나에서 실행되는 단일 프로세스(single process)이다. 각 kernel call은 단일 그리드를 생성한다.
* `Blocks` : 블록은 스레드의 모음이다. (collections of threads)
* `grid` : 그리드는 블록 모음이다. (Collections of blocks)



### Inbuilt variables

* `threadIdx.x` : 내장 변수(inbuilt variable)를 사용하여 해당 블록 안에서의 현재 스레드의 index를 얻을 수 있다.
* `blockIdx.x` : 그리드안의 현재 블록의 인덱스를 얻을 수 있다.
* `blockDim.x` : 블록안의 스레드의 개수는 내장 변수를 사용하여 얻을 수 있다.
* `gridDim.x` : 내장변수를 사용하여 그리드의 크기를 얻을 수 있다.

GPU가 가장 잘하는 일, 대규모 병렬 처리 및 부동 소수점 연산(massive parallelism and floating point operation)을 수행할 수 있다.

``` C
// Program : vector_add.c
#include <stdio.h>
#include <cuda.h>

#define N  10000000

__global__ void vector_add(float *a, float  *b, float *out, int n) {
    int index = threadIdx.x;
    int stride = blockDim.x
    for(int i=0; i<n; i++) {
        out[i] = a[i] + b[i];
    }
}   

int main() {
    // declaring memory in host
    float *h_a, *b, *out;
    
    // declaring memory in device
    float *d_a;
    
    // allocating memory on host
    h_a   = (float*)malloc(sizeof(float) * N);
    b     = (float*)malloc(sizeof(float) * N);
    out   = (float*)malloc(sizeof(float) * N);
   
   // initializing h_a and b
    for(int i=0; i<N; i++) {
        h_a[i] = 0.1f;
        b[i]   = 0.2f;
    } 
    
    // allocating memory in device and copying host data  to device
    cudaMalloc((void**)&d_a, sizeof(float) * N);
    cudaMemcpy(d_a, h_a, sizeof(float) * N, cudaMemcpyHostToDevice);    
    vector_add<<<1,256>>>(h_a, b, out, N);
    
    // deallocating memory from device
    cudaFree(d_a);

    // deallocating memory from host
    free(h_a);
    free(b);
    free(out);
    
    // returning success
    return 0;
}
```

스레드의 `kernal configuration`은 `<<<M, N>>>`를 통해 전달된다. CUDA는 32의 거듭제곱으로 커널을 실행한다. 여기서, thread(`threadIdx`)의 값은 1에서 256까지이다. 블록의 값 `(blockDim.x)`은 256이다. `<<<1,1>>>`로 설정하면, index는 1이고 stride는 1이 된다. 그러면 vector_add의 코드는 다음과 같다.

``` C
for(int i=0; i<0;i++){
   ...
}
```

각 스레드는 256의 stride로 배열을 반복한다. 즉, 첫번째 반복의 경우 스레드 0은 배열의 0번째 요소를 계산한다. 두번째 반복에서는 256번째 요소를, 세번째 반복에서는 256 + 256 = 512 요소를 계산한다. 

반복 `i`에 대한 각각의 `n`번째 요소와 'stride' (현재 처리되고 있는 요소)는 
반복을 위한 각 `n`th 요소 `i`와 `stride` 현재 처리중인 요소는 `n + i * stride`이다.

<img src = 'https://miro.medium.com/max/963/1*jrNyqD0pVFjW2_9FZX_qvQ.png'>



### Components of GPU

GPU에는 2가지 주요 구성요소가 있다.

* `global memory` : CPU의 RAM과 동일하다. device와 host 모두에서 접근될 수 있다.
* `Streaming Multiprocessor` : 실제 연산을 수행하는 device. 평신도 용어로 그것의 `CUDA cores`.

CUDA GPU에는 **SM**이라고 하는 여러 병렬 프로세서가 있다. 각 SM은 여러 병렬 프로세서로 구성되며 여러 동시(concurrent) 스레드 블록을 실행할 수 있다. 그것을 활용하자. 우리는 이미 블록 크기 256으로 정의했다. 이제 우리는 블록 크기로 요소의 수를 나눈 그리드의 크기를 찾아야 한다.

``` C
int BLOCKS_NUM = (N + BLOCK_SIZE — 1) / BLOCK_SIZE;
vector_add<<<BLOCKS_NUM, BLOCK_SIZE>>>(h_a, b, out, N);
```

이제 우리는 배열의 모든 요소를 덮기에 충분한 그리드가 있다고 가정하여 커널 코드를 작성한다.

``` C
int index = blockIdx.x * blockDim.x + threadIdx.x;
int stride = blockDim.x * gridDim.x;
```

<img src = 'https://miro.medium.com/max/963/1*DD1XMY8vvM66WLlGDHYcww.png'>

이러한 유형의 코드를 grid style loops 라고 한다. 자세한 내용은 [이곳](https://developer.nvidia.com/blog/cuda-pro-tip-write-flexible-kernels-grid-stride-loops/)을 참조하자.

``` C
// Program : vector_add_cuda_add_1.c
#include <stdio.h>
#include <cuda.h>

#define N  10000000
#define BLOCK_SIZE  256

// __global__ indicates that function runs on GPU.
__global__ void vector_add(float *a, float  *b, float *out, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = index; i < n; i += stride) {
        out[i] = a[i] + b[i];
    }
}   


int main() {
    // declaring memory in host
    // h_a is a convention for host variable
    float *h_a, *b, *out;
    
    // declaring memory in device
    // d_a is the convention for device variable
    float *d_a;

    // allocating memory on host
    h_a   = (float*)malloc(sizeof(float) * N);
    b     = (float*)malloc(sizeof(float) * N);
    out   = (float*)malloc(sizeof(float) * N);
   
  // initializing a and v
    for(int i=0; i<N; i++) {
        h_a[i] = 0.1f;
        b[i]   = 0.2f;
    } 
    cudaMalloc((void**)&d_a, sizeof(float) * N);
    cudaMemcpy(d_a, h_a, sizeof(float) * N, cudaMemcpyHostToDevice);  
    
    int BLOCKS_NUM = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
    vector_add<<<BLOCKS_NUM, BLOCK_SIZE>>>(h_a, b, out, N);
    
    // deallocating memory from device
    cudaFree(d_a);

    // deallocating memory from host
    free(h_a);
    free(b);
    free(out);
  
    return 0;
}
```


### pros

* **사용 용이성(Easy to use)** : CUDA API를 사용하면 GPU에 대한 심층지식 없이도 GPU를 사용할 수 있다. 그리고 CUDA는 기본적으로 NVIDIA 확장이 있는 C와 함께 사용된다. 최소한의 코드 변경으로 종료 코드(exiting code) 기반에서 구현될 수 있다.
* **성능(Performance)** : NVIDIA는 하드웨어와 API를 모두 만든다. 이를 통해 GPU에서 최대 성능을 제공하도록 API를 미세조정할 수 있다.


### cons

* **Proprietary software** : NVIDIA는 CUDA의 소유자이며, 폐쇄형 아키텍처를 갖고 있다. 시스템에서 실행하려면 NVIDIA 장치와 CUDA sdk tools가 필요하다.
* **Only simple loops** : CUDA는 재귀(recursion)를 구현할 수 있지만 구현하기가 어렵고 피하기 어렵다.



## Reference

* https://medium.com/geekculture/introduction-to-cuda-7bf6909ea57c

---



# Dive into basics of GPU, CUDA & Accelerated programming using Numba in Python

이 글에서는 GPU, CUDA 및 Numba의 기본에 대해 이야기하겠다. 또한 Numba를 사용하는 것이 CPU와 GPU 모두에서 일상적인 코드에서 어떻게 눈에 띄는 차이를 만드는지 간략하게 논의할 것이다.

Numba를 배우려면 이 [Kaggle Notebook](https://www.kaggle.com/general/274291)을 보자. 여기서는 기본 이론에 더 중점을 둘 것이다.

블로그의 주요동기 - 딥러닝 실무자들은 종종 GPU의 기능과 사용사례 및 용도에 따라 어떤 GPU를 사용할 수 있는지에 대해 이야기한다. 이 분야에 있기 때문에 GPU와 CUDA를 매일 사용하기 때문에 GPU와 CUDA의 구성요소를 이해하는 것이 중요하다!

아래 주제를 이해하기 위해 내가 참조한 모든 리소스를 첨부했다. 해당 링크를 자유롭게 보자.



### 1. Brief intro to Numba

Numba는 numpy 배열(및 계산), 긴 수학연산 및 루프와 관련된 함수에 가장 적합한 Python용 just-in-time compiler이다(just-in-time은 코드가 미리 컴파일하는 대신 런타임 중에 컴파일됨을 의미한다.)

Numba를 사용할 때, 함수에서만 작동한다. 즉, 전체 Python 응용 프로그램이나 함수의 코드 일부를 최적화하지 않는다. Python의 인터프리터를 대체하지는 않지만 실행속도를 높이는데 도움이 된다. Numba는 우리가 사용하는 변수에 데이터 유형(data type)을 지정하여 코드를 가속화한다. 파이썬에서는 int나 float를 언급하지 않는다. Python의 인터프리터는 컴파일하는 동안 자체적으로 수행하므로 속도가 느려진다. 따라서 Numba는 미리 int32 또는 float32와 같은 데이터 유형을 할당한다.

그러나 Numba는 우리가 작성하는 모든 코드를 최적화할 수 없다, 그것은 특정 데이터 유형에서는 작동하지 않음을 의미한다. 문서를 참조하자. 

Numba의 대안은 C/C++의 pyCUDA 및 CUDA이다. 그러나 Numba의 주요 장점 중 하나는 CPU에 대한 코드도 가속화하는 반면, 다른 2가지는 Nvidia GPU에만 해당된다는 것이다.



### 2. What is CUDA & why use it?

CUDA는 **Compute Unified Device Architecture**의 약자이다. API이며 병렬 컴퓨팅 플랫폼(parallel computing platform)이다. Nvidia의 GPU에만 해당된다.

잠깐, 병렬 컴퓨팅 플랫폼이란 무엇일까? 여러 프로세서가 복잡한 큰 문제를 분해하는 여러 계산을 동시에 실행하는 컴퓨팅 아키텍처 유형이다.

GPU는 일반적으로 병렬계산이 요구되는 곳에 사용된다.

#### What are CUDA cores?

CUDA 코어는 Nvidia GPU의 코어 수일뿐이다.(Nvidia->CUDA). 복잡한 연산/계산을 수행하는 병렬 컴퓨팅을 전문으로 하는 high-tech 코어이다. 코어 수가 많을수록, 계산속도가 빨라진다!

#### Why do we use CUDA?

더 작은 문제로 나눌 수 있고 각 하위문제(sub-problem)가 다른 하위문제의 결과와 독립적인 복잡한 계산의 경우, 여기 내 친구 병렬 컴퓨팅이 그림에 등장한다. 

이러한 엄청난 수의 하위 문제를 더 빠르고 병렬로 계산하려면, cpu에 비해 코어가 너무 많은 GPU를 가져와야 한다. 

이제 각 하위문제는 GPU의 각 코어에서 계산되는 개별작업으로 가정할 수 있다. 가벼운 속도로 작업을 완료하기 위해 GPU에 의존하기 때문에, 코드도 예상되는 형식이어야 한다. 

이제 GPU가 예상하는 방식으로 작업을 코딩하려면 어떻게 해야할까? 따라서 CUDA는 Nvidia의 자체 GPU에서 작동하여 GPU에서 코드(예: 컨볼루션 연산)를 효율적으로 실행할 수 있도록 도와주는 nvidia의 API 및 프로그래밍 언어이다. CUDA를 코드에서 쓰기 위해, CUDA toolkit을 설치해야 한다.



### 3. CUDA Kernels

GPU에서 실행되어야 하는 함수를 커널(kernel)이라고 한다. 함수를 커널로 지정하기 위해 우리는 **함수 한정자(function qualifiers)**라고 불리는 것을 사용한다. 이들은 파이썬의 데코레이터와 유사하다. 함수 한정자는 함수 바로 위에 배치된다.

몇가지 함수 한정자는 C/C++에서 다음과 같다.

``` 
__global__ - 이 한정자로 표시된 함수는 커널이 된다. 이는 커널이 host에서 호출될 수 있고 device에서 실행됨을 의미한다.

__device__ - 이 한정자로 표시된 함수는 함수/커널이 device에서만 호출될 수 있고 device에서 실행됨을 나타낸다(장치(device) = GPU)
```

Numba에서 간단한 커널은 어떻게 생겼을까? 다음은 숫자를 2로 곱한 예시이다.

``` Python
from numba import cuda
import numpy as np
@cuda.jit # decorator to run function on GPU using CUDA
def multiply_kernel(x, out):
    idx = cuda.grid(1) # create 1-D grid of threads
    out[idx] = x[idx] * 2  # in each thread, save value of x[i]*2
n = 4096
x = np.arange(n).astype(np.int32)
d_x = cuda.to_device(x)
d_out = cuda.device_array_like(d_x) # create output array
blocks_per_grid= 32  # number blocks in each grid
threads_per_block = 128  # number threads in each block
multiply_kernel[blocks_per_grid, threads_per_block](d_x, d_out)
cuda.synchronize() # Wait for GPU to complete the task
print(d_out.copy_to_host()) # copy data from GPU to CPU/Host
```

Output will be something like this : [0, 2, 4, 6, ..., 8192]



### 4. Threads, Blocks, Grid and Wrap in CUDA

* Threads - 스레드는 커널을 실행하는 단일실행단위(single execution unit)이다.
* Blocks - 여러 스레드가 함께 블록을 형성한다. 각 블록에는 최대 1024개의 스레드가 있다.

하나의 GPU는 몇개의 블록을 병렬로 실행할 수 있다. 아주 좋은 GPU는 10블록을 사용하여 10분안에 작업을 완료할 수 있고, 평균 GPU는 동시에 2블록만 사용하여 20분안에 작업을 완료할 수 있다. 각 블록의 스레드 수는 1024개로 동일하게 유지된다. 따라서 이는 코드를 한번 변경하지 않고도 동일한 코드를 다른 GPU에서 실행할 수 있음을 의미한다. 엔비디아 덕분에!

* Grid - 여러 블록이 그리드를 형성한다.

* Warp - 모든 작업을 수행하려면, 스레드에 리소스가 필요하다. 스트리밍 멀티프로세서(Streaming Multiprocessors)는 리소스를 스레드에 개별적으로 직접 할당하지 않는다. 대신 스레드를 Wrap이라고 하는 32개(최대, 더 적을 수 있음) 그룹으로 나눈 다음, 리소스를 할당하여 작업을 실행한다. 이제 블록에 많은 Wrap이 있다고 말할 수 있다.

* Half-wrap - 임의의 주어진 시간에 단지 16개의 스레드만이 SM에서 실행될 것이다. 그러므로 우리는 memory access의 단위로 half-wrap을 고려한다. (Fermi 이전 아키텍처에 적용가능한)

<img src = 'https://miro.medium.com/max/1240/1*wXVTl_nL3BdfSCSxaSzsAg.png'>



### 5. Streaming Multiprocessors

우리의 커널은 SM 또는 스트리밍 멀티 프로세서에 의해 실행된다. GPU는 그 중 몇개로 구성된다. 이들은 더 낮은 클럭 속도(lower clock rate)로 실행되고 작은 캐시를 갖는다. 주요 작업은 여러 스레드 블록을 병렬로 실행하는 것이다. 자신의 스레드 블록 중 하나가 실행을 완료하면, SM은 다음 스레드 블록을 순차적으로 선택한다.

> Nvidia 문서에서 - 호스트 CPU의 CUDA 프로그램이 커널 그리드를 호출하면, 그리드 블록이 열거되고 사용가능한 실행용량이 있는 멀티프로세서에 배포된다. 스레드 블록의 스레드는 하나의 다중 프로세서에서 동시에 실행되고, 여러 스레드 블록은 하나의 다중 프로세서에서 동시에 실행할 수 있다. 스레드 블록이 종료되면, 비어있는 멀티프로세서에서 새 블록이 시작된다.

각 SM에는 여러 캐시(L1 cache, Constant cache, Texture cache), 공유 메모리(Shared memory), 부동소수점 및 정수연산을 위한 Wrap schedulers 및 실행코어가 있다. SM의 공유 메모리는 SM의 스레드 블록으로 나뉜다. 스레드가 공유 메모리에 제대로 액세스하지 않으면, 스레드가 서로 뒤에 대기하여 성능이 저하되는 "bank conflict"이 발생한다. 하나의 SM은 주어진 시간에 둘 이상의 블록을 실행할 수 있다.



### 6. SMIT Architecture

Nvidia 자체 문서에서 가장 좋은 설명을 찾았으므로 여기에 추가했다. **Nvidia의 CUDA 문서에서 언급한 바와 같이 (참조4), (섹션에서 인용: 하드웨어 구현)**

> "멀티프로세서는 수백개의 스레드를 동시에 실행하도록 설계되었다. 이러한 많은 스레드를 관리하기 위해, SIMT 아키텍처에서 설명하는 SIMT(Single-Instruction, Multi-Thread)라는 고유한 아키텍처를 사용한다. 하드웨어 멀티스레딩에 자세히 설명된대로, 동시 하드웨어 멀티스레딩을 통한 광범위한 스레드 수준 병렬처리뿐만 아니라, 단일 스레드 내의 명령수준 병렬처리를 활용하여 명령이 파이프라인된다. cpu 코어와 달리, 순차적으로 발행되며 분기예측(branch prediction)이나 추측실행(speculative execution)이 없다."



### 7. Coalesced Memory Access

주어진 스레드 셋트가 단일 트랜잭션에서 global memory의 연속(contiguous) 블록에서 동시에 읽고 쓸 때, 이를 병합(coalesd)memory access라고 한다. 통합 메모리 액세스는 1.x 및 2의 CUDA 컴퓨팅 기능이 있는 GPU에만 적용된다. 최신 GPU는 전역 메모리에 액세스하는 더 복잡한 방법을 사용한다.



### 8. Bank conflicts

Banks는 무엇인가? - 병렬로 접근할 수 있는 공유 메모리는 Banks라는 모듈들로 나눠진다. 

공유 메모리에서는, 4 bytes를 1 word라고 한다. Nvidia GPU의 공유 메모리에는 32개의 banks(현대의 그래픽 카드에)가 있다. 공유 메모리의 각 연속적인 워드는 하나의 bank에 속한다. 이것은 word 0이 bank 0에 속하고 word 1이 bank 1에 속한다는 것을 의미한다. 하나의 wrap은 이러한 32개 은행의 모든 순열로 요청을 보낼 수 있다. 공유 메모리를 뱅크로 분할할 때, 2개의 뱅크에서 어떤 메모리 주소라도 발생하면, 뱅크 충돌이 발생한다.

만약 하나의 wrap안의 모든 스레드가 단일 bank로부터의 값을 읽고, 값은 한번만 읽히고 스레드 간에 공유된다. 이를 broadcast라고 한다.



### 9. Numba on CPU and GPU

#### On CPU

Monte Carlo 방법을 사용하여 PI의 값을 추정하면서, 범위를 10k로 전달한다. Numba가 없는 CPU에서는 10.8ms(7회 실행의 평균, 각 100회 루프)가 걸렸지만, Numba에서는 237 $\mu$s (7회 실행의 평균, 각각 100회 루프)가 걸렸다. 45배 빨라졌다!!

``` Python
@jit(nopython=True)
def monte_carlo_pi(n):
    acc = 0
    for i in range(n):
        x = random.random()
        y = random.random()
        if (x**2 + y**2) < 1.0:
            acc += 1
    return 4.0 * acc / n
%timeit monte_carlo_pi(10000)
```

이것은 [Analytics Vidhya Numba tutorial](https://analyticsindiamag.com/make-python-code-faster-with-numba/)의 예제코드이다. Numba로 코드를 가속화하려면, 설명서를 참조하고 그에 따라 복잡한 계산만 수행하도록 함수를 수정하는 것이 가장 좋다. Numba에서 지원하는 유형이 제한되어 있기 때문에, 이러한 작은 함수를 만드는 것은 Numba의 잠재력을 최대한 활용하는 것을 도울 것이다.



#### On GPU

``` Python
@cuda.jit
def add_kernel(x, y, out):
    idx = cuda.grid(1)
    out[idx] = x[idx] + y[idx]
n = 4096
x = np.arange(n).astype(np.int32) 
y = np.ones_like(x)   
d_x = cuda.to_device(x) 
d_y = cuda.to_device(y) 
d_out = cuda.device_array_like(d_x) 
threads_per_block = 128
blocks_per_grid = 32
```

CUDA의 이 추가 함수는 100 $\mu$s(7회 실행의 평균, 각갂 10000회 루프)가 소요되고 동일한 입력에 대한 초보자 추가 코드는 880$\mu$s(7회 실행의 평균, 각각 1000회루프)가 소요된다. CUDA에서 동일한 작업이 8.8배 더 빠르다!

그러나 CUDA 함수에 걸리는 시간은 계산을 위한 것일뿐이다. 여기서 우리는 호스트 메모리에서 GPU 메모리로 데이터를 이동한 다음 GPU 메모리에서 호스트 메모리로 다시 출력을 이동하는데 걸리는 시간을 고려하지 않았다.

그래도 Numpy 또는 기본 수학연산을 사용하여 복잡한 계산을 수행하는 함수와 함께 사용할 수 있다고 생각한다. 모델을 추론하는 동안 해당함수가 1초마다 호출되면 전체 성능이 크게 향상된다!



### Conclusion

GPU와 CUDA의 기본개념을 탐색하는 것은 재미있었다. 또한 Numba에 노출되면, CPU에서도 코드를 가속화할 수 있다. 아마도 CPU에서 추론을 실행할 때, Numba가 파이프라인의 일부를 가속화하는 데 도움이 될 수 있다.

Numba를 탐색하려면 위에서 공유한 Kaggle 노트북을 따라하자. 


### Reference

* https://sahilchachra.medium.com/dive-into-basics-of-gpu-cuda-accelerated-programming-using-numba-in-python-a0be21aa00b7
    - https://numba.readthedocs.io/en/stable/user/5minguide.html
    - https://www.techopedia.com/definition/3978/just-in-time-compiler-jit-compiler#:~:text=A%20just%2Din%2Dtime%20(,fly%20as%20the%20program%20executes.
    - https://www.kaggle.com/harshwalia/1-introduction-to-cuda-python-with-numba
    - https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
    - https://www.youtube.com/playlist?list=PLKK11Ligqititws0ZOoGk3SW-TZCar4dK
    - https://blogs.nvidia.com/blog/2012/09/10/what-is-cuda-2/
    - https://deeplizard.com/learn/video/6stDhEA0wFQ
    - https://developer.nvidia.com/blog/cuda-refresher-cuda-programming-model/
    - http://thebeardsage.com/cuda-streaming-multiprocessors/
    - https://stackoverflow.com/questions/32226993/understanding-streaming-multiprocessors-sm-and-streaming-processors-sp
    - https://stackoverflow.com/questions/2207171/help-me-understand-cuda/2213744#2213744
    SMs — https://stackoverflow.com/questions/3519598/streaming-multiprocessors-blocks-and-threads-cuda
    - https://stackoverflow.com/questions/10460742/how-do-cuda-blocks-warps-threads-map-onto-cuda-cores
    - https://cvw.cac.cornell.edu/gpu/coalesced
    - Half wrap — https://forums.developer.nvidia.com/t/why-only-half-warp/15915/6
    - Bank conflic — https://stackoverflow.com/questions/3841877/what-is-a-bank-conflict-doing-cuda-opencl-programming#:~:text=The%20shared%20memory%20that%20can,the%20advantages%20of%20parallel%20access.
    - Bank conflict — https://www.youtube.com/watch?v=CZgM3DEBplE
    - Bank conflict — https://www.generacodice.com/en/articolo/666174/%C2%BFqu%C3%A9-es-un-conflicto-banco?-(hacer-la-programaci%C3%B3n-cuda-/-opencl)

---
