





# 컨볼루션 신경망의 역사

Convolutional Neural Networks, 줄여서 CNN은 많은 현대 컴퓨터 비전 시스템의 중추를 형성한다. 이 포스트는 1950년대의 생물학적 실험을 시작으로 CNN의 기원에 대해 설명한다.


## 단순 세포와 복잡한 세포

1959년 [David Hubel](https://en.wikipedia.org/wiki/David_H._Hubel)과 [Torsten Wiesel](https://en.wikipedia.org/wiki/Torsten_Wiesel)은 인간의 시각피질에 있는 "단순 세포"와 "복합 세포"를 설명했다. 그들은 두 종류의 세포가 패턴인식에 사용된다고 제안했다. "[단순 셀](https://en.wikipedia.org/wiki/Simple_cell)"은 다음 이미지와 같이 특정 방향의 모서리와 막대에 응답한다.

<img src = 'https://miro.medium.com/max/378/0*_RM5ia1cfmkTJ7HD'>

"복잡한 셀"은 특정 방향의 가장자리와 막대에도 반응하지만 이러한 가장자리와 막대가 장면 주위로 이동할 수 있고 셀이 여전히 응답한다는 점에서 단순한 셀과 다르다. 예를 들어, 단순한 셀은 이미지 하단의 가로 막대에만 응답할 수 있는 반면, 복잡한 셀은 이미지 하단, 중간 또는 상단의 수평막대에 응답할 수 있다. 복잡한 세포의 이러한 속성을 "공간 불변성"이라고 한다.

이 [백서](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC1890437/)의 그림 1은 단순 셀과 복잡한 셀의 차이점을 보여준다.

Hubel과 Wiesel은 1962년에 복잡한 셀이 동일한 방향(예: 수평막대)을 선호하지만 다른 수용필드(예: 이미지의 하단, 중간 또는 상단)를 선호하는 여러 단순 셀의 출력을 "합산"하여 공간불변성을 달성한다고 제안했다. 단순한 셀 미니언 무리로부터 정보를 수집함으로써 복잡한 셀은 어디에서나 발생하는 수평막대에 반응할 수 있다.(!)

단순한 감지기를 "합산"하여 더 복잡한 감지기를 만들 수 있다는 이 개념은 인간의 시각 시스템 전체에서 볼 수 있으며 컨볼루션 신경망 모델의 기본 기반이기도 하다.

(참고 : 이 개념을 극단으로 치면 "[할머니 세포](https://en.wikipedia.org/wiki/Grandmother_cell)", 즉 뇌 어딘가에 할머니의 시각에만 반응한는 단일 뉴런이 있다는 개념을 얻게 된다.)



## 네오코그니트론

1980년대에 kunihiko Fukushima 박사는 단순 세포와 복잡한 세포에 대한 Hubel와 Wiesel의 연구에서 영감을 받아 "[네오코그니트론](https://en.wikipedia.org/wiki/Neocognitron)" 모델을 [제안](https://www.rctn.org/bruno/public/papers/Fukushima1980.pdf)했다. 신인지 모델에는 "S-세포" 및 "C-세포"라는 구성요소가 포함된다. 이들은 생물학적 세포가 아니라 오히려 수학적 연산이다. "S-cell"은 모델의 첫번째 레이어에 있고 모델의 두번째 레이어에 있는 "C-cell"에 연결된다. 전반적인 아이디어는 "단순에서 복잡한" 개념을 포착하여 시각적 패턴 인식을 위한 계산모델로 바꾸는 것이다.


## 필기 인식을 위한 컨볼루션 신경망

현대 CNN(Convolutional Neural Networks)에 대한 첫번째 작업은 1990년대에 네오코그니트론에서 영감을 받아 이루어졌다. Yann LeCun et al.은 ["Gradient-Based Learning Applied to Document Recognition"](http://yann.lecun.com/exdb/publis/pdf/lecun-01a.pdf) 이라는 논문에서 간단한 특징을 점점 더 복잡한 특징으로 통합하는 CNN 모델이 필기문자 인식에 성공적으로 사용될 수 있음을 보여주었다.

구체적으로, LeCun et al. [손으로 쓴 숫자의 MNIST 데이터베이스](http://yann.lecun.com/exdb/mnist/index.html)를 사용하여 CNN을 훈련했다. MNIST는 0, 1, 2, 3, 4, 5, 6, 7, 8 ,9의 실제 레이블과 쌍을 이루는 손으로 쓴 숫자의 이미지를 포함하는 이제 유명한 데이터셋이다. CNN 모델은 다음을 제공하여 MNIST 에서 훈련된다. 예시 이미지이고 이미지에 표시되는 숫자를 예측하도록 요청한 다음 숫자 ID를 올바르게 예측했는지 여부에 따라 모델 설정을 업데이트한다. 최첨단 CNN 모델은 오늘날 MNIST 숫자 분류에서 거의 완벽한 정확도를 달성할 수 있다.

<img src = 'https://miro.medium.com/max/653/0*N12IeN008JYr-7YC'>

[MNIST 데이터 세트에서 손으로 쓴 숫자의 예](https://en.wikipedia.org/wiki/MNIST_database)

이 작업의 직접적인 결과 중 하나는 이제 자동필기 인식기술을 사용하여 주소를 읽는 [기계별로 메일이 분류된다](https://mailingsystemstechnology.com/article-2813-Optical-Character-Recognition-A-Backbone-for-Postal-and-Mail-Sorting-Applications.html)는 것이다.


## 모든 것을 볼 수 있는 컨볼루션 신경망

1990년대와 2000년대 초반에 걸쳐 연구자들은 CNN 모델에 대한 추가작업을 수행했다. 2012년 무렵 CNN은 AlexNet이라는 CNN이 ImageNet 챌린지에서 최첨단 성능 라벨링 사진을 달성한 후 엄청난 인기를 얻었다. 이는 오늘날 계속된다. Alex Krizhevsky et al.이 수상한 AlexNet 모델을 설명하는 ["ImageNet Classification with Deep Convolutional Neural Networks"](https://proceedings.neurips.cc/paper/2012/file/c399862d3b9d6b76c8436e924a68c45b-Paper.pdf) 라는 논문을 발표했다.


MNIST와 유사하게 [ImageNet](https://image-net.org/)은 무료로 사용가능한 공개 데이터셋인 이미지와 해당 실제 레이블이다. ImageNet은 0~9로 표시된 손글씨 숫자에 초점을 맞추는 대신 "자연 이미지" 또는 "양서류", "가구" 및 "사람"을 비롯한 다양한 설명어로 레이블이 지정된 세계의 그림에 중점을 둔다. 레이블은 인간의 엄청난 노력을 통해 획득했다(예: 수동 레이블 지정 - 누군가에게 각 이미지에 대해 "이 사진은 무엇인지"를 적어달라고 요청). ImageNet은 현재 14,197,122개의 이미지를 포함하고 있다.

<img src = 'https://miro.medium.com/max/678/0*mkpvMkCbiSi8d_K4'>

[ImageNet 데이터세트의 예시 이미지](https://www.researchgate.net/figure/Examples-in-the-ImageNet-dataset_fig7_314646236)

지난 몇년 동안 CNN은 자연 이미지 설명(ImageNet, [CIFAR-10](https://www.cs.toronto.edu/~kriz/cifar.html), [CIFAR-100](https://www.cs.toronto.edu/~kriz/cifar.html) 및 [VisualGenome](https://visualgenome.org/) 포함), 얼굴 인식 수행([CelebA](https://www.kaggle.com/datasets/jessicali9530/celeba-dataset/code) 포함), 의료 이미지 분석([흉부 X-레이](https://stanfordmlgroup.github.io/competitions/chexpert/) 포함, [사진 포함](https://www.nature.com/articles/nature21056))에서 탁월한 성능을 달성했다. 피부병변 및 조직병리학 슬라이드). 이 웹사이트인 ["CV Datasets on the web"](http://www.cvpapers.com/datasets.html)에는 연구자들이 CNN 및 기타 종류의 컴퓨터 비전 모델을 훈련하고 평가하는 데 사용할 수 있는 50개 이상의 레이블이 지정된 이미지 데이터 세트의 광범위한 목록이 있다. 기업들은 [Seeing AI](https://www.theverge.com/2017/7/12/15958174/microsoft-ai-seeing-app-blind-ios)를 포함하여 많은 흥미로운 애플리케이션을 개발하고 있다. 시각 장애인에게 주변 환경을 음성으로 설명할 수 있는 스마트폰 앱.


## CNN과 휴먼 비전?

대중 언론은 종종 신경망 모델이 "인간 두뇌에서 직접 영감을 받은" 방법에 대해 이야기한다. 어떤 의미에서는 CNN과 인간의 시각 시스템이 모두 "단순에서 복잡한" 계층구조를 따르기 때문에 사실이다. 그러나 실제 구현은 완전히 다르다. 뇌는 세포를 사용하여 구축되고 신경망은 수학적 연산을 사용하여 구축된다.

이 비디오, [Jason Yosinski의 "Deep Visualization Toolbox"](https://www.youtube.com/watch?v=AgkfIQ4IGaM)는 CNN이 어떻게 간단한 특징을 취하여 얼굴이나 책과 같은 복잡한 특징을 감지하는 데 사용하는지에 대한 더 나은 이해를 위해 볼 가치가 있다.

<img src = 'https://miro.medium.com/max/678/0*IZMPjtUnMG4CIbgK'>

## 결론

컴퓨터비전은 지난 수십년 동안 먼 길을 왔다. 새로운 개발이 미래에 이 분야를 변화시키고 자동화된 방사선 영상 해석 및 자율주행 자동차와 같은 기술을 향상시킬지 상상하는 것은 흥미진진하다.


추천 이미지 정보

<img src = 'https://miro.medium.com/max/770/1*YkpC07EkYV8elxWxLnn5yA.jpeg'>

위의 이미지는 [서부초원 종달새](https://en.wikipedia.org/wiki/List_of_birds_of_North_Dakota)를 보여준다. 200종의 새를 보여주는 6,033개의 이미지가 포함된 Caltech-UCSD Birds 200 데이터세트를 포함하여 CNN이 새 종을 자동으로 인식하도록 훈련시키는데 사용할 수 있는 다양한 새 데이터 세트가 있다. 비슷한 맥락에서 [iNaturalist](https://www.inaturalist.org/pages/computer_vision_demo)는 조류 및 기타 많은 종을 포함하는 크라우드 소싱 자동 종 식별 시스템을 구축하고 있다. 그러한 시스템은 언젠가는 보존생물학에서 크게 사용될 수 있다.









# History of Convolutional Neural Networks



<img src = 'https://miro.medium.com/max/1400/1*uMtwKpqoRRrSuKjI3ce7KA.jpeg'>

딥러닝의 세상에서 CNN(Convolutional Neural Network)은 이미지 분석에 가장 일반적으로 사용되는 인공 신경망의 한 종류이다. 처음부터 CNN 아키텍처는 급속한 발전을 거쳤으며 최근에는 이전에 인간의 실행/개입을 통해서만 가능하다고 여겨졌던 결과를 달성하였다. 당면한 직업과 해당 제약조건에 따라 오늘날 다양한 아키텍처를 사용할 수 있다. 이것들은 너무 깊어서 완전히 시각화할 수 없으며 종종 블랙박스로 취급된다. 그러나 그들은 항상 그랬는가? CNN 아키텍처의 역사를 탐구하는 것이 흥미롭지 않은가? 이 역사 속으로 빠르게 들어가려면 안전벨트를 메어라.



## 1. 네오코그니트론(1980)

Neocognitron은 이러한 종류의 첫번째 아키텍처였으며 아마도 CNN의 초기 선구자였을 것이다. 특징 추출, 계층 풀링, 신경망에서 컨볼루션 사용의 개념이 도입되었고 마지막으로 [Neocognitron](https://www.rctn.org/bruno/public/papers/Fukushima1980.pdf). 네트워크 구조는 척추동물의 시각 신경계 구조에서 영감을 받았다. 전체 네트워크에서 S-세포(단순 셀 또는 저차 하이퍼컴플렉스 셀) 및 C-셀(복합 셀 또는 고차 하이퍼컴플렉스 셀)의 교대 레이어가 있는 S-셀 및 위치 허용에 의한 특징 추출 프로세스 C 세포에 의한 이동이 반복되었다.이 과정에서 하위 단계에서 추출된 로컬 기능이 점차 더 글로벌 기능으로 통합된다. 손으로 쓴 (일본어) 문자 인식 및 기타 패턴 인식 작업에 사용되었으며 컨볼루션 신경망의 길을 열었다.

<img src = 'https://miro.medium.com/max/1400/1*_BhBtMMzuJMRdYc9NIz0HA.png'>


## 2. LeNet-5 (1989-1998)

Convolutional Neural Networks라는 이름은 실제로 Yann LeCun과 팀의 LeNet 설계에서 유래하였다. [논문링크](http://vision.stanford.edu/cs598_spring07/papers/Lecun98.pdf) 1989년에서 1998년 사이에 필기숫자 인식 작업을 위해 크게 개발되었다.

<img src = 'https://miro.medium.com/max/1400/1*0qE3TDF8iWxczJ5qHSsrLw.png'>

전체 아키텍처는 [CONV-POOL-CONV-POOL-FC-FC] 였다. 스트라이크가 1인 5x5 컨볼루션 필터를 사용하였다. 풀링(서브샘플링) 레이어는 보폭이 2인 2x2 였다. 매개변수는 약 60k이다.

CNN의 최신 아키텍처에 대한 크레딧은 'ImageNet 대규모 시각적 인식 챌린지 (ILSVRC)`라는 [ImageNet(데이터세트) 분류 챌린지](https://image-net.org/index.php)에 있다. 2010년에 시작되어 연구원들이 공통 데이터셋에서 특히 이미지 분류를 위해 기계학습 및 컴퓨터비전 모델을 벤치마킹하기 위해 상당한 노력을 기울였다. 성능은 Top-1 오류와 Top-5 오류로 측정되었다. 2010년의 승률은 28.2%로 신경망 없이 이루어졌다. 2011년 연구원들은 28.2%에서 25.8% 오류율로 점수를 개선하였다. 그림 3은 해당 오류가 있는 모든 승자를 막대로 표시한다.

<img src = 'https://miro.medium.com/max/1400/1*6IbJkXh__RyNSOEWc1Nu7w.png'>

마침내 2012년 Alex Krizhevsky와 Geoffrey Hinton은 오늘날까지 AlexNet으로 널리 사용되는 CNN 아키텍처를 내놓았다. 이 아키텍처는 오류를 25.8%에서 16.4%로 줄였다. 이는 당시 상당한 개선이었다.


### 3. 알렉스넷(2012)

[AlexNet](https://papers.nips.cc/paper/2012/file/c399862d3b9d6b76c8436e924a68c45b-Paper.pdf)은 ImageNet 챌린지의 첫번째 우승자였으며 CNN을 기반으로 했으며 2012년부터 매년 CNN이 챌린지에서 우승했다. 다른 심층 및 얕은(전통적인) 기계학습 방법을 훨씬 능가한다.


<img src = 'https://miro.medium.com/max/1276/1*ladZUTTKfBs4i0UozYW92A.png'>

AlexNet에는 총 8개의 레이어(5개의 컨볼루션 레이어와 3개의 완전연결 레이어)가 있으며 분명히 ImageNet 데이터셋에서 훈련되었다. 응답 정규화 계층이라는 정규화 계층이 처음 도입되었다. 주어진 레이어의 채널에서 특정 위치의 모든 값을 정규화하였다. 또한 활성화 함수로 ReLU(Rectified Linear Unit)도 도입했다. 약 60M 매개변수가 있다. (LeNet의 매개변수 수를 기억할 수 있는가?) 흥미롭게도 합성곱 계층은 누적 계산의 약 90~95%를 포함하지만 매개변수의 약 5%만 포함한다.


### 4. 지에프넷(2013)

바로 다음 해 2013년에 ZFNet(설계자 Zeiler와 Fergus의 이름을 따서 명명됨)은 ImageNet LSRVC의 승자가 되었다. ZFNet의 아키텍처는 AlexNet의 아키텍처와 동일하지만 하이퍼매개변수에 몇 가지 변경사항이 있다. 전환 레이어 1에서 필터 크기가 (스트라이드 4가 있는 11x11)에서 (스트라이드 2가 있는 7x7)로 변경되었다. Conv 레이어 3, 4, 5에서 필터의 수가 각각 384, 384, 256에서 512, 1024, 512로 증가했다. 하이퍼매개변수를 신중하게 선택하면 상위 5개 오류가 16.4%에서 11.7%로 크게 감소하였다.


### 5. VGGNet(2014)

2014년으로 넘어가면서 2014년에 목격된 주요 공헌 중 하나는 [VGGNet](https://arxiv.org/abs/1409.1556). VGGNet은 Visual Geometry Group(옥스포드 대학)에서 발명한(아케이드) 아키텍처를 나타낸다. CNN을 더 깊게 만들면 ImageNet 분류 문제에서 문제를 더 잘 해결하고 오류율을 낮출 수 있다고 주장했다. 다양한 깊이의 여러 아키텍처가 시도되었다. (그림 5) 그룹은 깊이를 증가시킴으로써 기능에서 더 많은 비선형성을 모델링할 수 있다는 철학에 따라 작업했으며 따라서 핵심 기여는 깊이를 설계의 중요한 구성요소로 고려하는 것이었다. 균질한 아키텍처와 더 작은 수용필드는 디자인의 다른 주요 기능이었다. 이 아키텍처는 2014년 ImageNet 챌린지에서 2위를 차지했다. 특히 VGG-16(13Conv + 3 FC 레이어)은 138M 매개변수로 구성되며 48.6MB의 상당한 메모리 오버헤드가 있다. (빠른 비교를 위해 AlexNet은 1.9MB)


<img src = 'https://miro.medium.com/max/1094/1*OB5esxNTzCFDgR-7nCsAEg.png'>


VGG-19라는 더 깊은 변형도 설계되었다. 그러나 VGG16보다 약간만 더 좋았다. 그래서 VGG16까지는 Depth에 따라 성능이 계속 향상되었지만, 일정 뎁스 이후에는 포화되는 것 같았다. 왜 이런 일이 발생했고 어떻게 해결되었는지 알고 싶은가? -지켜보자!!


## 6. 구글넷(2014)

2014년 Google은 [GoogLeNet](https://arxiv.org/abs/1409.4842)을 도입했다. GoogLeNet은 매개변수의 수, 메모리 사용량 및 계산을 줄이기 위해 더 큰 효율성을 목표로 더 깊은 네트워크에 다시 초점을 맞추었다. 최대 22개의 레이어까지 더 깊어졌지만 완전히 연결된 (FC) 레이어는 없었다. FC 레이어를 제거하여 매개변수의 총 수는 5M으로 감소했다. (AlexNet보다 12배, VGG보다 약 28배 적음). '인셉션 모듈'이라는 모듈이 도입되었다. GoogleNet은 ILSVRC-14 분류 우승자가 되었다. (6.7% 상위 5개 오류 포함).

<img src = 'https://miro.medium.com/max/1370/1*IbE7MhHPjct82N_eAOvWtg.png'>


시작모듈(병렬분기가 있는 로컬장치)은 접근방식의 핵심 혁신이었다. 이 모듈/블록은 네트워크 전체에 걸쳐 여러번(컨볼루션 계층 대신) 쌓인다. 그것은 건축의 기초가 되었고 따라서 이름이 시작되었다. 아키텍처는 Inception-v1이라고도 한다. 또한 Inception-v3 및 Inception-v4도 각각 2015년과 2016년에 도입되었다. (Quick Note : Inception-v2는 주로 실험용이었다.)

<img src = 'https://miro.medium.com/max/1400/1*vw2X71W-TKrYN2Gt3ndpeg.png'>

그냥 엉뚱한 생각이다. '일반' 컨볼루션 신경망에 더 깊은 레이어를 계속 쌓으면 어떻게 될까? - 실제로 깊은 모델은 얕은 모델보다 성능이 떨어진다. 하지만 왜? - 초기 추측은 더 깊은 모델이 얕은 모델보다 훨씬 크기 때문에 과적합된다는 것이다. 그러나 이것이 사실이라면 훈련세트의 성능은 더 깊은 모델에서 더 좋았을 것이다. 그러나 훈련 및 테스트 세트 모두에서 20계층 심층 네트워크가 56계층 네트워크보다 더 나은 성능을 발휘하는 것으로 나타났다. 따라서 훈련 세트의 성능을 고려하면 더 깊은 (56계층) 네트워크가 과소적합되었다고 말할 수 있다(!). 그렇다면 신경망의 깊이가 증가했을 때 실제로 어떤 일이 일어났는가? - 배니싱 그라디언트 문제. 실제로, 시그모이드 함수의 기울기는 0.25보다 작으며 연쇄규칙이 적용될 때 각 전달 레이어에 의해 각 0.25 값의 곱셈은 충분히 깊은 네트워크에 대한 모든 실제적인 목적을 위해 전체 기울기를 점점 더 작게 만든다. 그리고 그레디언트는 역전파를 통해 초기 레이어에 도달하지 않으며 초기 레이어는 가중치 업데이트 및 학습없이 임의 초기화에 갇히게 된다. 더 깊은 모델의 성능을 최소한 얕은 모델만큼 보장할 수 있을까? - ResNet에 답이 있다.


### 7. ResNet(2015)

Kaiming He et. al. [Microsoft Research의 ResNet 논문](https://arxiv.org/abs/1512.03385) 아키텍처에서 ID(건너뛰기) 연결을 통해 서로 연결되는 '잔여블록'에 대한 아이디어를 내놓았다.

<img src = 'https://miro.medium.com/max/1400/1*qLO4_-Ths1JBoSr4M6m_CQ.png'>

잔여 네트워크는 많은 잔여블록의 스택이다(그림 9). 각 잔여블록에는 2개의 3x3 conv 레이어가 있다.

<img src = 'https://miro.medium.com/max/412/1*THPReAkJRDNxublD64Pq3A.png'>

팀은 스킵 연결을 대중화하고 모델의 일반화 능력을 손상시키지 않으면서 최대 152개의 레이어까지 더 깊이 들어갔다. 더 깊은 네트워크(ResNet-50+)의 경우 "병목" 레이어를 사용하여 효율성을 개선하였다.(GoogLeNet과 유사)

ResNet은 모든 ILSVRC 및 COCO 2015 대회에서 1위를 차지했으며 여러 애플리케이션에서 계속 인기있는 선택이 되었다. 사용된 철학은 MobileNet, EfficientNet과 같은 최신 아키텍처를 포함하여 Wide Residual Networks(WideResNet), ResNeXt(Deep Neural Networks), 확률적 깊이가 있는 Deep Networks, DenseNets(Densely Connected Convolutional Networks)와 같은 몇 가지 최근 아키텍처에서 확장되었다. 그리고 세넷. 더 새롭고 더 새로운 아키텍처의 도입으로 이야기는 영원히 계속된다...











## Reference

* https://medium.com/appyhigh-technology-blog/convolutional-neural-networks-a-brief-history-of-their-evolution-ee3405568597
* Fukushima, K. and Miyake, S., 1982. Neocognitron: A self-organizing neural network model for a mechanism of visual pattern recognition. In Competition and cooperation in neural nets (pp. 267–285). Springer, Berlin, Heidelberg.
* LeCun, Y., Bottou, L., Bengio, Y. and Haffner, P., 1998. Gradient-based learning applied to document recognition. Proceedings of the IEEE, 86(11), pp.2278–2324
* Krizhevsky, A., Sutskever, I. and Hinton, G.E., 2017. ImageNet classification with deep convolutional neural networks. Communications of the ACM, 60(6), pp.84–90.
* Simonyan, K. and Zisserman, A., 2014. Very deep convolutional networks for large-scale image recognition. arXiv preprint arXiv:1409.1556.
* C. Szegedy et al., “Going deeper with convolutions,” 2015 IEEE Conference on Computer Vision and Pattern Recognition (CVPR), 2015, pp. 1–9, doi: 10.1109/CVPR.2015.7298594.
* He, K., Zhang, X., Ren, S. and Sun, J., 2016. Deep residual learning for image recognition. In Proceedings of the IEEE conference on computer vision and pattern recognition (pp. 770–778).
* Fei-Fei Li, Justin Johnson and Serena Yeung, CS231n course, Stanford, Spring 2019
* Prof. Vineeth N Balasubramanian, noc20-cs88, IIT Hyderabad, NPTEL, Fall 2020

* https://towardsdatascience.com/a-short-history-of-convolutional-neural-networks-7032e241c483
* https://glassboxmedicine.com/2019/04/13/a-short-history-of-convolutional-neural-networks/