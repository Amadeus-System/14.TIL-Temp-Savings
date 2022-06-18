
* Date : 2022-06-18
* Last Devised : 2022-06-18


# Generative Adversarial Networks - The Story So Far

GAN(Generative Adversarial Networks)는 지난 몇년동안 이미지 생성을 위한 최첨단 알고리즘이었다. 이 글에서는 BigGAN, StyleGAN 등을 포함하여 이 분야에서 가장 중요한 혁신에 대해 배울 것이다.

<img src = 'https://blog.floydhub.com/content/images/size/w2000/2019/06/benjamin-behre-429210-unsplash.jpg'>

Ian Goodfellow가 2014년에 맥주 한잔에 GAN(Generative Adversarial Networks)에 대한 아이디어를 구상했을 때 그는 아마도 필드가 이렇게 빨리 발전할 것이라고 예상하지 못했을 것이다.


<img src = 'https://regmedia.co.uk/2018/10/01/biggan.jpg'>

내가 어디로 가는지 모르겠다면, 방금 본 이미지는 완전히, 부인할 수 없는 100%... 가짜였다.

또한, 나는 이것들이 포토샵, CGI 편집 또는 (Nvidia가 현재 그들의 멋진 신기술이라고 부르는 것으로 공백을 채우는 것을 의미하지 않는다)

내 말은 이 이미지가 GPU 계산에서 덧셈, 곱셈 및 엄청난 양의 현금을 과도하게 사용하여 완전히 생성된다는 것을 의미한다.

작업을 가능하게 하는 알고리즘을 생성적 적대 네트워크(GAN을 작성하는 긴 방법이다. 여전히 머신러닝 약어 영역에 갇혀있는 사람들을 위해) 라고 하며, 지난 몇년동안 더 많은 혁신이 있었다. Facebook에서 개인정보 스캔들이 있었던 것보다 효과가 있다.




2014년 바닐라 GAN에 대한 모든 개선사항을 요약하는 것은 왕좌의 게임 시즌8을 반복해서 시청하는 것만큼 어렵다. 그래서 대신에 나는 지난 몇년동안 GAN 연구에서 가장 멋진 결과 뒤에 숨겨진 핵심 아이디어를 요약할 것이다.

Transposed convolution과 Wasserstein distance와 같은 개념은 자세히 설명하지 않겠다. 대신 이러한 개념에 대해 빠르게 학습하는 데 사용할 수 있는 몇가지 최고의 리소스에 대한 링크를 제공하여 이러한 개념이 큰 그림에 어떻게 맞는지 확인할 수 있다.

아직 읽고 있다면 딥러닝의 기본사항을 알고 있고, [컨볼루션 신경망이 작동하는 방식](https://blog.floydhub.com/building-your-first-convnet/)을 알고 있다고 가정하겠다.

즉, GAN 풍경의 지도는 다음과 같다.

<img src = 'https://paper-attachments.dropbox.com/s_D85DDA7D01FD04AEE96825C4B90F1126BC7D080CA4F2947D4A5DEC07FAD6122C_1559841150851_Map.png'>


한 번에 한 단계씩 살펴보겠다. 여행을 시작하자.

1. GAN: 생성적 적대 네트워크
2. DCGAN: Deep Convolutional Generative Adversarial Network
3. CGAN: 조건부 생성 적대 네트워크
4. 싸이클GAN
5. CoGAN: 결합된 생성 적대 네트워크
6. ProGAN: Generative Adversarial Networks의 점진적 성장
7. WGAN: Wasserstein 생성적 적대 네트워크
8. SAGAN: Self-Attention Generative Adversarial Networks
9. BigGAN: 거대 생성 적대 네트워크
10. StyleGAN: 스타일 기반 생성 적대 신경망



## GAN : 생성적 적대 네트워크

<img src = 'https://blog.floydhub.com/content/images/2019/06/image.png'>

* [논문](https://arxiv.org/abs/1406.2661)
* [source](https://github.com/goodfeli/adversarial)
* [기타 훌륭한 리소스 : Ian Goodfellow의 NIPS 2016 튜토리얼](https://arxiv.org/abs/1701.00160)

지금, 나는 당신이 무슨 생각을 하는지 안다. 이런, 이미지의 저 소름끼치고 픽셀화된 엉망은 엑셀 시트를 축소하는 수학 멍청이가 만든 것처럼 보인다.

<iframe width="720" height="405" src="https://www.youtube.com/embed/UBX2QQHlQ_I" title="Stand-up comedy routine about Spreadsheets" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

글쎄, 당신이 어느 정도 옳다고 생각한다 (엑셀 부분 제외).

2014년에 Ian Goodfellow는 2개의 신경망이 서로 경쟁(또는 협업, 관점의 문제)하게 하는 혁신적인 아이디어를 제안했다.

한 신경망은 실제 데이터를 **생성**하려고 시도하고 (GAN은 모든 데이터 분포를 모델링하는데 사용할 수 있지만, 요즘은 주로 이미지에 사용됨) 다른 신경망은 실제 데이터와 생성기 네트워크에서 생성된 데이터를 **구별**하려고 한다.

생성기 네트워크는 판별자를 손실함수로 사용하고 매개변수를 업데이트하여 보다 사실적으로 보이기 시작하는 데이터를 생성한다.

<img src = 'https://skymind.ai/images/wiki/GANs.png'>



반면에 판별자 네트워크는 실제 데이터에서 가짜 데이터를 더 잘 찾아낼 수 있도록 매개변수를 업데이트한다. 그래서 그 역할도 더 좋아진다.

고양이와 쥐의 게임은 시스템이 소위 "평형"에 도달할 때까지 계속된다. 여기서 생성기는 판별자가 할 수 있는 최선은 무작위로 추측할 수 있을만큼 충분히 실제처럼 보이는 데이터를 생성한다.

바라건대, 이 시점에서 코드를 올바르게 들여쓰기하고 Amazon이 스팟 인스턴스를 종료하지 않기로 결정했다면(그런데 FloydHub에서 예약된 GPU 머신을 제공하기 때문에 이런 일이 발생하지 않음) 이제 정확한 생성기가 남게 된다. 훈련셋과 동일한 분포에서 새 데이터를 생성한다.

자, 이것은 명백히 GAN에 대한 매우 단순한 관점이다. 여기서 빼야 할 생각은 2개의 신경망을 사용하여 하나는 데이터를 생성하고 다른 하나는 가짜 데이터에서 실제 데이터를 분류하여 이론상 생성기가 생성할 수 있는 지점으로 수렴하도록 동시에 훈련할 수 있다는 것이다. 완전히 새롭고 현실적인 데이터.



## DCGAN : Deep Convolutional Generative Adversarial Network

<img src = 'https://blog.floydhub.com/content/images/2019/06/image-1.png'>

* [논문](https://arxiv.org/abs/1511.06434)
* [소스](https://github.com/floydhub/dcgan)
* [기타 훌륭한 리소스 : 중간기사](https://naokishibuya.medium.com/up-sampling-with-transposed-convolution-9ae4f2df52d0)

봐, 내가 시간을 좀 절약해줄게.

$$ \text{Convolutions} = \text{Good for images} $$

$$ \text{GANs} = \text{Good for generating stuff} $$

$$ \implies \text{Convolutions} + \text{GANs} = \text{Good for generating images} $$

돌이켜보면 Ian Goodfellow가 [Lex Fridman과의 팟캐스트](https://www.youtube.com/watch?v=Z6rxFNMGdn0&t=2487s)에서 지적했듯이 오늘날 딥러닝 및 이미지와 관련된 거의 모든 것이 딥러닝 및 컨볼루션이기 때문에 이 모델을 DCGAN(Deep Convolutional Generative Adversarial Network의 약자)이라고 부르는 것은 어리석은 것 같다..

게다가, 대부분의 사람들은 GAN을 접할 때 어쨌든 "심층 및 컨볼루션" 설정에서 GAN에 대해 배운다.

그럼에도 불구하고 GAN이 반드시 컨볼루션 기반 연산을 사용하지 않고 대신 표준 다층 퍼셉트론 아키텍처에 의존하던 때가 있었다.

DCGAN은 전치된 컨볼루션 연산 또는 "불행한" 이름인 [Deconvolution layer](https://datascience.stackexchange.com/questions/6107/what-are-deconvolutional-layers)라는 것을 사용하여 이를 변경했다.

Transposed convolutions는 업스케일링 작업으로 작동한다. 저해상도 이미지를 고해상도 이미지로 변환하는데 도움이 된다.

그러나 진지하게, 이 작업은 모든 최신 GAN 아키텍처의 기본이기 때문에 위의 리소스를 통해 전치된 컨볼루션에 대한 이해를 명확히 하여라.

시간이 조금 부족하다면 Transposed Convolution이 어떻게 작동하는지에 대한 훌륭한 요약을 하나의 간단한 애니메이션에서 찾을 수 있다.

<img src = 'https://paper-attachments.dropbox.com/s_D85DDA7D01FD04AEE96825C4B90F1126BC7D080CA4F2947D4A5DEC07FAD6122C_1559895100810_s_257816875AB071372D764C43DFB8A4901E0EBAB81800E986F1F30C17BAA9E957_1557221973576_no_padding_strides_transposed.gif'>

[source](https://arxiv.org/abs/1603.07285)



바닐라 컨브넷에서는 다른 작업과 함께 일련의 컨볼루션을 적용하여 일반적으로 더 낮은 차원의 벡터에 이미지를 매핑한다.

유사하게, 여러개의 전치된 컨볼루션을 순차적으로 적용하면 단일 저해상도 어레이를 생생한 풀컬러 이미지로 발전시킬 수 있다.

이제 계속하기 전에 GAN을 사용하는 몇 가지 고유한 방법을 탐색하기 위해 작은 접선을 시작하겠다.

<img src = 'https://paper-attachments.dropbox.com/s_D85DDA7D01FD04AEE96825C4B90F1126BC7D080CA4F2947D4A5DEC07FAD6122C_1559921735372_Map2.png'>



## CGAN : 조건부 생성 적대 네트워크

<img src = 'https://paper-attachments.dropbox.com/s_D85DDA7D01FD04AEE96825C4B90F1126BC7D080CA4F2947D4A5DEC07FAD6122C_1559840652472_Screenshot+2019-06-06+at+10.33.58+PM.png'>

* [논문](https://arxiv.org/abs/1411.1784)
* [소스](https://github.com/PacktPublishing/Advanced-Deep-Learning-with-Keras)
* [기타 훌륭한 리소스 : Blogpost](https://agustinus.kristia.de/techblog/2016/12/24/conditional-gan-tensorflow/)

원래 GAN은 무작위 노이즈에서 데이터를 생성한다. 즉, 개 이미지에 대해 훈련할 수 있고 더 많은 개 이미지를 생성할 수 있다.

고양이 이미지로 훈련할 수도 있다. 이 경우 고양이 이미지가 생성된다.

Nicholas Cage 이미지에서 훈련할수도 있다. 이 경우 Nicholas Cage 이미지가 생성된다.

당신은 또한 그것을 훈련시킬 수 있다.. 여기에서 패턴을 감지하기 바란다.

그러나 개와 고양이 이미지 모두에서 동시에 훈련하려고 하면 흐릿한 혼혈이 생성된다.

<img src = 'https://images.unsplash.com/photo-1509205477838-a534e43a849f?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjI2NzI5fQ'>


CGAN("조건부 생성적 적대 네트워크"의 약자)은 생성기에 고양이, 개 또는 Nicholas Cage와 같은 특정 클래스의 이미지만 생성하도록 지시하여 이 문제를 해결하는 것을 목표로 한다.

특히, CGAN은 원-핫 벡터를 연결한다. 와이랜덤 노이즈 벡터에지 다음과 같은 아키텍처를 생성한다.

<img src = 'https://paper-attachments.dropbox.com/s_D85DDA7D01FD04AEE96825C4B90F1126BC7D080CA4F2947D4A5DEC07FAD6122C_1559840765144_Screenshot+2019-06-06+at+10.35.29+PM.png'>


이제 동일한 GAN에서 고양이와 개를 모두 생성할 수 있다. 🐈 🐕


## 사이클 GAN

<img src = 'https://cdn-images-1.medium.com/max/1600/1*5DG4hHjxAyWTfV1J3mRH_A.png'>

* [논문](https://arxiv.org/abs/1703.10593v6)
* [소스](https://github.com/junyanz/CycleGAN)
* 기타 유용한 리소스 : [CycleGAN 프로젝트 페이지](https://junyanz.github.io/CycleGAN/), [Medium 기사](https://towardsdatascience.com/turning-fortnite-into-pubg-with-deep-learning-cyclegan-2f9d339dcdb0)


GAN은 이미지 생성에만 사용되지 않는다. 그들은 또한 위의 이미지와 같이 말 + 얼룩말 생물(zorses? hobras?)을 만들 수 있다.

이러한 이미지를 생성하기 위해 CycleGAN은 이미지 대 이미지 번역이라는 문제를 해결하는 것을 목표로 한다.

CycleGAN은 최첨단 이미지 합성을 추진하는 새로운 GAN 아키텍처가 아니다. 대신 GAN을 사용하는 현명한 방법이다. 따라서 원하는 아키텍처에 이 기술을 자유롭게 사용할 수 있다.

즉시, 나는 당신이 이 [논문](https://arxiv.org/abs/1703.10593v6)을 읽을 것을 권한다. 그것은 매우 잘 작성되었으며 초보자도 쉽게 접근할 수 있다.

여기서 작업은 네트워크를 훈련시키는 것이다. $G(x)$ 소스 도메인의 이미지를 매핑하는 $x$ 대상 도메인으로 $y$.

그러나 "이것이 일반 딥러닝이나 스타일 이전과는 어떻게 다른가요?"라고 묻는다.

음, 아래 이미지가 잘 요약되어 있다. CycleGAN은 쌍을 이루지 않은 이미지에서 이미지로의 번역을 수행한다. 이것은 우리가 훈련하는 이미지가 같은 것을 나타낼 필요가 없다는 것을 의미한다.

<img src = 'https://cdn-images-1.medium.com/max/1200/1*oZsw1JaGkKPxWKKvVUWlyg.png'>



우리가 많은 컬렉션을 가지고 있다면 이미지를 DaVinci-ify하는 것이 (상대적으로) 쉬울 것이다. (이미지, 다빈치의 이미지 페인팅) 한 쌍.

불행히도, 그 친구는 너무 많은 그림을 완성하지 못했다.

그러나 CycleGAN은 짝을 이루지 않은 데이터를 훈련한다. 따라서 동일한 이미지가 2개 필요하지 않다.

반면에 스타일 전송을 사용할 수 있다. 그러나 그것은 단지 하나의 특정 이미지의 스타일을 추출하여 다른 이미지로 전송할 것이다. 즉, 말에서 얼룩말로 번역할 수는 없다.

그러나 CycleGAN은 이미지의 한 도메인에서 다른 도메인으로의 매핑을 학습한다. 그래서 우리는 모네의 모든 그림의 집합체라고 할 수 있다.

<img src = 'https://blog.floydhub.com/content/images/2019/06/68747470733a2f2f6a756e79616e7a2e6769746875622e696f2f4379636c6547414e2f696d616765732f70686f746f327061696e74696e672e6a7067.jpeg'>

그들이 사용하는 방법은 매우 우아하다. CycleGAN은 2개의 생성기로 구성되며, $G$, 그리고 $F$, 그리고 2개의 판별자, $D_x$, 그리고 $D_y$.

$G$에서 이미지를 가져온다.(X) 그리고 그것을 어떤 이미지에 매핑하려고 시도한다.(Y) 판별자 D_Y 이미지가 다음에 의해 생성되었는지 여부를 예측한다. G 또는 실제로 Y.

비슷하게, F에서 이미지를 가져온다.(Y) 그리고 그것을 어떤 이미지에 매핑하려고 시도한다.(X) 그리고 판별자 D_x 이미지가 다음에 의해 생성되었는지 여부를 예측한다.(F 또는 실제로 X)

4개의 네트워크는 모두 강력한 생성기가 남을 때까지 일반적인 GAN 방식으로 훈련된다. G 그리고 F, 이미지를 이미지로 변환하는 작업을 충분히 수행할 수 있다. (D_y 그리고 d_x 각각)





























---

# Generative Adversarial Networks - History and Overview

최근에는 생성 모델링의 인기가 높아졌다. 특히, Ian Goodfellow et al.에 의해 소개된 Generative Adversarial Networks 또는 GAN이라고 하는 비교적 최근의 모델이다. 현실적인 샘플 생산에 대한 약속을 보여준다. 이 블로그 포스팅은 두 부분으로 나누어져 있다. Part-1은 GAN에 대한 소개, GAN의 역사 및 다양한 응용 프로그램으로 구성된다. Part-2는 이미지 샘플을 생성하기 위한 GAN(코드 포함)의 구현으로 구성된다.



## 1부 - GAN 이해

### 생성 모델링

먼저 생성 모델이 무엇인지, 판별 모델과 어떻게 다른지 살펴보겠다. 입력 데이터 $x$와 해당 출력 레이블 $y$가 있다고 가정한다. 판별 모델은 조건부 확률분포 $P(y|x)$를 직접 학습하려고 한다. 반면에 생성 모델은 결합확률분포 $P(x, y)$를 학습하려고 한다. 이것은 Bayes 규칙을 사용하여 $P(y|x)$로 변환될 수 있다. 그러나 추가적으로 판별 모델과 달리 생성 모델은 공동분포 $P(x, y)$를 사용하여 가능한 $(x, y)$ 샘플을 생성할 수 있다.


### 과대 광고는 무엇인가?

그렇다면 생성 모델을 연구하려는 이유는 무엇일까? 특히 이미 사용가능한 데이터가 너무 많기 때문에 단순히 더 많은 데이터를 생성하는 것이 큰 문제인지 궁금해 할 수 있다. 그러나 실제로 이것은 여러 용도로 사용될 수 있다. 예를 들어, 특정 필체로 작성된 일부 텍스트를 생성 모델에 대한 입력으로 제공하여 동일한 필체로 더 많은 텍스트를 생성할 수 있다. 생성 모델, 특히 GAN은 인공 환경을 생성하는 데 사용할 수 있는 강화학습 탐색에도 사용할 수 있다. 다른 응용 프로그램에는 스케치를 이미지로 변환, 이미지 노이즈 제거, 저해상도 이미지를 고해상도로 변환, 예술 생성, 위성 이미지를 지도로 변환 등이 있다. 다양한 응용 프로그램 외에도,


### 수년에 걸친 생성 모델

생성 모델링이 무엇이며 왜 유용한지에 대한 기반을 마련했으므로 생성 모델링의 다양한 접근 방식을 살펴보겠다. 모델을 비교하기 위해 모두 최대가능성을 수행하도록 설명할 수 있다.


<img src = 'https://miro.medium.com/max/958/1*otb47mG5KQWNh91prmyxzg.png'>


위의 그래프는 Ian Goodfellow가 NIPS 튜토리얼에서 설명한대로 다양한 생성 모델 제품군을 보여준다. 이제 위에서 언급한 모델 제품군에서 인기있는 접근 방식의 장단점을 살펴보겠다.



### 완전히 가시적인 믿음 네트워크

그들은 확률의 연쇄규칙을 사용하여 벡터에 대한 확률분포를 벡터의 각 구성원에 대한 곱으로 분해한다.


<img src = 'https://miro.medium.com/max/1024/1*EEOWOQSAOams58A4gMfjkQ.png'>


이 제품군에서 가장 인기있는 모델은 PixelCNN이다.


<img src = 'https://miro.medium.com/max/1400/1*vioNjVcI6vpplIuvTLWyQg.jpeg'>


FVBN의 가장 큰 단점은 샘플 생성 속도가 매우 느리다는 것이다. 새 샘플을 생성할 때마다 모델을 다시 실행해야 한다. 이것은 병렬로 수행할 수 없다.


### 변수의 변화에 따른 모델(Non-linear ICA)

이러한 모델은 가우스와 같은 간단한 분포로 시작하여 비선형 함수를 사용하여 분포를 다른 공간으로 변환한다. 이것의 주요 단점은 변환이 가역적으로 설계되어야 하고 잠재변수가 데이터와 동일한 차원을 가져야 한다는 것이다. 따라서 5000 픽셀을 생성하려면 5000개의 잠재변수가 있어야 한다.


### 변형 자동 인코더

Variational autoencoder가 작동하는 방식은 밀도함수 $log p(x)$에서 랜덤 변수 $z$를 주변화하는 것이다. 이것은 다루기 어렵기 때문에 변동 근사를 사용한다. 모델은 데이터의 로그 가능성에 대한 하한을 최대화하려고 한다.


<img src = 'https://miro.medium.com/max/720/1*Eg_zDuOlOvpS5yuOtFcC4Q.jpeg'>


여기서 주요 단점은 분포 $q$가 완벽할 경우 모델이 점근적으로 일관된다는 것이다. 그렇지 않으면 데이터의 하한과 실제 밀도 사이에 간격이 생긴다. 또 다른 단점은 생성된 샘플의 품질이 상대적으로 낮다는 것이다.



### 볼츠만 기계

볼츠만 기계는 에너지 함수로 정의할 수 있으며 특정 상태의 확률은 각 에너지 값에 비례한다. 이것을 실제 확률분포로 변환하기 위해 재정규화는 합을 여러 상태로 나누어 수행된다. 이 합계는 몬테카를로 방법을 사용하여 근사를 요구하는 다루기 어렵다. 단점은 이러한 방법, 특히 Markov Chain Monte Carlo 방법이 고차원 공간에서 잘 수행되지 않는다는 것이다. 따라서 [MNIST](http://yann.lecun.com/exdb/mnist/)와 같은 이미지에서는 잘 수행될 수 있지만, [ImageNet](https://image-net.org/)의 이미지에서는 비슷한 성능을 얻지 못할 것이다.


### 생성적 적대 네트워크

이제 다른 인기있는 생성 모델에 대해 다루었으므로 GAN을 살펴보고 나머지 모델과 비교하는 방법을 살펴보겠다.

GAN은 위의 모델에 언급된 많은 단점을 극복하도록 설계되었다. 완전 가시적 신념 네트워크와 달리 GAN은 잠재 코드를 사용하며 병렬로 샘플을 생성할 수 있다. Variational Autoencoder와 달리 GAN은 점근적으로 일관성이 있다. 또한 GAN에는 Markov 체인이 필요하지 않으므로 Boltzmann Machines에 비해 이점이 있다. 마지막으로, GAN은 매우 주관적이고 현재 PixelCNN과 같은 모델이 경쟁하는 주제이지만 최고의 샘플을 생성하는 것으로 종종 높이 평가된다.


<img src = 'https://miro.medium.com/max/1012/1*_d22i5gAB8UWL68EnjXQwA.png'>



### GAN의 작동 방식

GAN에 대해 연구할 가치가 있는 이유를 확인했으므로 이제 GAN이 실제로 어떻게 작동하는지 자세히 살펴보겠다.

GAN의 기본 아이디어는 생성자와 판별자라는 두 플레이어 간의 게임으로 해석될 수 있다. 생성기는 기차 데이터와 동일한 기본 분포를 따르는 샘플을 생성하려고 시도한다. 판별기는 생성기에서 생성된 샘플(가짜 데이터)과 기차 세트의 실제 데이터를 구별하려고 시도한다. 생성기의 목표는 실제 데이터와 구별할 수 없는 샘플을 생성하기 위해 기본 분포를 밀접하게 근사하여 판별자를 속이는 것이다. 반면, 판별기의 목표는 실제 데이터에서 가짜 데이터를 식별하는 것이다. 판별자는 단순히 데이터가 진짜인지 가짜인지 판별하는 이진분류 문제의 작업을 수행한다. 이 게임의 일반적인 유추는 위조자와 경찰의 유추이다. 위조자는 경찰을 속이기 위해 돈을 위조하고 최대한 합법적인 것처럼 보이게 하는 생성기와 같다. 경찰은 위조된 돈을 식별하는 것을 목표로 하는 판별자와 같다.


<img src = 'https://miro.medium.com/max/1400/1*KF-XzsW2F44sCxlgdDy_9w.png'>


생성기는 경사하강법으로 학습할 수 있는 매개변수가 있는 미분가능한 함수 $G$이다. $G$에 대한 입력은 잠재변수에 대한 일부 사전분포에서 잠재벡터 $z$를 샘플링하여 얻는다. 따라서 본질적으로 $z$는 구조화되지 않은 노이즈의 벡터이다. $G$는 모델에서 샘플 $x$를 얻기 위해 $z$에 적용되며, 이는 이상적으로는 기차 세트의 실제 데이터와 유사해야 한다. 생성기와 마찬가지로 판별자도 경사하강법으로 학습할 수 있는 매개변수가 있는 미분가능한 함수 $D$이다. 함수 $D$, $G(z)$에서 얻은 샘플 $x$에 적용될 때 이상적으로는 샘플이 가짜임을 나타내는 0에 가까운 값을 출력해야 한다. 데이터의 실제 샘플이 $D$에 대한 입력으로 제공되면 1에 가까운 값을 출력해야 한다.

$\theta(D)$와 $\theta(G)$는 각각 D와 G의 매개변수이다. 판별자는 비용 $J(D)(\theta (D), \theta (G))$를 최소화하려고 하지만 $\theta (G)$에 대한 제어권한이 없지만 생성자는 $J(G)(\theta (D), \theta (G)) \theta (D)$를 제어할 수 없다. 따라서 $J(D)$가 $\theta (D)$ 및 $J(G)$에 대해 최소가 되도록 $(\theta (D), \theta (G))$에 대한 내쉬균형 값을 찾고 싶다.는 $\theta (G)$에 대해 최소이다.

그렇다면 실제로 훈련은 어떻게 이루어지는가? 훈련 절차는 예를 들어 Adam과 같은 최적화 알고리즘을 선택하고 실제 훈련 데이터와 G에 의해 생성된 샘플의 두 미니배치 데이터에 동시에 적용하는 것이다. 또한 한 플레이어를 다른 플레이어보다 더 자주 업데이트할 수 있다.



### 생성기 및 판별기 비용

알고리즘이 진행되는 방식은 각 플레이어의 비용에 따라 다르다. 비용을 지정하는 가장 간단한 방법은 생성기 비용이 판별자 비용의 음수인 Minimax 게임을 사용하는 것이다. 그렇다면 판별자가 최대화하고 생성자가 최소화하려는 이 비용은 정확히 얼마인가? 그것은 단순히 판별자의 출력과 실제 레이블(실제/가짜) 사이의 표준 교차 엔트로피 함수이다.

<img src = 'https://miro.medium.com/max/1400/1*Fqbu2D0jvv5es9lx98iF7A.png'>


$J(D)$의 첫번째 항은 실제 데이터를 판별자에 공급하는 것을 나타내며 판별자는 데이터가 실수임을 나타내는 1을 예측하는 로그 확률을 최대화하려고 한다. 두번째 항은 $G$에 의해 생성된 샘플을 나타낸다. 여기서 판별자는 데이터가 가짜임을 나타내는 0을 예측하는 로그 확률을 최대화하려고 한다. 반면에 생성기는 판별자가 정확할 로그 확률을 최소화하려고 한다. 이 문제에 대한 해결책은 판별자 손실의 안장점인 게임의 평형점이다.

이 Minimax 게임의 주요 문제는 판별기가 점점 더 똑똑해지면 생성기의 기울기가 사라진다는 것이다. 이 문제를 해결하는 한 가지 방법은 단순히 판별자의 비용 부호를 뒤집는 대신 교차 엔트로피 함수에서 인수의 순서를 뒤집는 것이다.

<img src = 'https://miro.medium.com/max/640/1*BmABwFGxU70CITe909PmjA.png'>


생성기는 이제 판별자가 틀릴 확률을 최대화하려고 한다. 이제 균형은 단일 가치 함수로 설명될 수 없으며 이 특정비용에 대한 동기는 훨씬 더 발견적이다.



### 확장 GAN

초기 GAN 자체는 실제로 대규모 응용 프로그램으로 잘 확장되지 않는다. 이를 극복하기 위해 Radfort at al에서 Deep Convolution GAN 아키텍처를 도입하였다. 원래 GAN은 이미 심층적이고 컨볼루션적이었지만 DCGAN은 더 많은 컨볼루션 계층을 강조하고 배치 정규화와 같은 기술을 추가로 사용한다. 학습과정을 보다 안정적으로 만들기 위해 생성기의 마지막 계층을 제외한 모든 계층에 일괄 정규화를 적용한다.

<img src = 'https://miro.medium.com/max/1400/1*wm4IDdMOigfTEXNXjFKuBw.png'>


### 더 많은 응용 프로그램

GAN이 AI 세계를 폭풍으로 몰아넣었다는 것은 신화가 아니며 실제로 여기에 있다. 이 섹션을 마치기 전에 오늘날 GAN의 몇 가지 매력적인 응용 프로그램을 살펴보겠다.

널리 사용되는 응용 프로그램 중 하나는 초해상도 기술을 사용하여 저해상도 이미지에서 고해상도 이미지를 생성하는 것이다.


<img src = 'https://miro.medium.com/max/1400/1*rkSvwXsWcJ2Aqu6gAMskTA.png'>


2016년 Scott Reed et al은 GAN을 사용하여 텍스트에서 사실적인 이미지를 합성하는 데 최근에 또 다른 발전을 이루었다.


<img src = 'https://miro.medium.com/max/1400/1*h9ziqVloZE2nLmOQH-LDug.png'>


앞서 설명한 것처럼 GAN은 강화학습에도 많은 응용 프로그램을 가지고 있다. 그들은 또한 몇 가지 예를 들면 이미지 노이즈 제거 및 예술 생성에 적용되었다.



## 2부 - GAN 구현

이제 GAN이 무엇이고 정확히 어떻게 작동하는지 알게 되었으므로 공식적으로 이 글의 흥미로운 부분에 도달하였다. 이제 시작하고 코드를 작성할 시간이다.

GAN의 가장 두드러진 응용 프로그램은 이미지 생성이므로 GAN에서 이미지 생성기 코딩에 익숙해지는 것이 좋다. 코드는 이미지 세트를 입력으로 사용하고 유사한 이미지 세트를 출력으로 생성해야 한다. 대부분의 사람들은 종종 MNIST와 같은 이미지로 시작하고 GAN을 사용하여 손으로 그린 숫자를 더 많이 생성하려고 한다. 여기에서는 ImageNet의 이미지를 입력으로 사용한다. 이 이미지는 매우 높은 차원이므로 이미지 생성에 DCGAN을 사용할 것이다.

입력을 위해 ImageNet의 '식물' 데이터셋의 이미지가 사용된다. 각 이미지는 128x128 이미지를 얻기 위해 크기가 조정되었다.

<img src = 'https://miro.medium.com/max/512/1*a-g7_k_bUO2WG90pAiMjLw.png'>

다음 DCGAN의 구현은 TensorFlow에 있다. 이 구현의 핵심은 DCGAN이라는 Python 클래스에 포함되어 있다. 여기서 모델을 정의하고 교육하는 방법을 정의한다.

생성기는 아래에 정의되어 있다. 선형 레이어와 4개의 컨볼루션 레이어로 구성된다. linear 및 conv2dTranspose 메서드는 레이어를 얻는데 사용되는 도우미 함수이다. Batch normalization은 마지막 레이어를 제외한 모든 레이어에 적용된다.

<img src = 'https://miro.medium.com/max/1400/1*E9AXCJIID9BjrFWImgrfBg.png'>


다음으로 판별자를 정의한다. 4개의 컨볼루션 레이어와 선형 레이어가 뒤따르는 것으로 정의한다. 도우미 함수 relu를 사용하여 사용자 지정 활성화 함수(Leaky ReLU)를 정의한다.

<img src = 'https://miro.medium.com/max/1400/1*LnipgrZJIiRooKKIKZySJg.png'>


이제 생성기 및 판별기 모델을 만들 수 있다. 동일한 매개변수를 공유하는 2개의 판별자를 정의한다. 하나는 기차 데이터에서 실제 이미지의 미니배치가 제공되는 반면, 다른 하나는 생성기에 의해 생성된 이미지의 미니배치가 제공된다.


<img src = 'https://miro.medium.com/max/1400/1*rB7mdryw6NAuhhk4PNfAGg.png'>


다음으로 생성기와 판별기에 대한 손실함수를 정의해야 한다. 블로그 Part-1에서 설명한 것처럼 판별자의 출력과 실제 레이블(실제/가짜) 사이에 교차 엔트로피 기능을 사용한다. 여기서 '실제'라는 레이블은 1에 해당하고 '가짜'라는 레이블은 0에 해당한다. 따라서 판별자는 실제 이미지에 대해 1에 가까운 값을 출력하고 생성기에 의해 생성된 이미지에 대해 0에 가까운 값을 출력하는 것을 목표로 해야 한다. 생성기 손실은 Part-1에 명시된 휴리스틱을 사용하여 계산된다. 판별자가 틀릴 확률을 기반으로 계산된다. 즉, 생성자는 판별자가 생성하는 이미지에 대해 1에 가까운 값을 출력하기를 원할 것이다.


<img src = 'https://miro.medium.com/max/1400/1*k6uqvQTU1MzDp3k7toq0TA.png'>


훈련을 시작하기 전에 먼저 위의 손실을 최소화하기 위해 최적화 함수를 정의해야 한다. 여기에서 생성자와 판별자 모두에 대해 학습률 = 0.0002인 Adam 최적화 프로그램을 사용한다. 여기서 d_theta는 판별자의 모든 매개변수를 나타내고 g_theta는 제너레이터의 모든 매개변수를 나타낸다.

<img src = 'https://miro.medium.com/max/1400/1*QuP9i-AegqxfPkxjym5t0w.png'>

마지막 단계는 실제로 데이터 훈련과 이미지 생성을 시작하는 것이다. 각 에포크에 대해 하나는 기차 이미지에서, 다른 하나는 샘플링 $Z$에서 2개의 미니배치 쌍이 생성된다. 또한 판별자 손실이 0이 되는 것을 방지하기 위해 판별자가 업데이트될 때마다 생성기가 2번 업데이트된다.


<img src = 'https://miro.medium.com/max/1400/1*_5f2iX0_0k9pEArHKg-v7w.png'>



### 결과

다음은 ImageNet의 공장 데이터를 입력으로 (128x128로 크기 조정) DCGAN을 실행할 때 얻은 출력이며, Epoch 수는 250으로 설정되어 있다.

<img src = 'https://miro.medium.com/max/512/1*5kIiFpkG_lRhCg7bZ8g44Q.png'>

4가지 손실 각각은 아래에 표시된다.

<img src = 'https://miro.medium.com/max/1400/1*VfN3VnmmgJrX5m6i4bWyWw.png'>

<img src = 'https://miro.medium.com/max/1400/1*ELTnivYLwXMxq87RukjasA.png'>

<img src = 'https://miro.medium.com/max/1400/1*qDYvcNaUhwH6srw_DljbwQ.png'>

<img src = 'https://miro.medium.com/max/1400/1*4MNlXBYoZZsad-YBksuW0Q.png'>


## 결론 및 향후 작업

대부분의 에포크에서 생성자 손실은 판별자 손실보다 낮은 것으로 나타났다. 이것은 판별자가 업데이트될 때마다 생성기가 두번 업데이트되었다는 사실에 기인할 수 있다.

완벽하지는 않지만 생성된 많은 이미지가 임의의 픽셀 분포가 아니라 식물/꽃과 유사하다. 따라서 DCGAN은 자체 이미지를 지능적으로 구성할 수 있다고 결론지을 수 있다. 그러나 개선의 여지가 많다. 이 구현의 주요 제한사항 중 하나는 계산 리소스가 부족하다는 것이다. 이미지 생성 자체는 계산 집약적인 작업이다. 이 특정 예에서 이미지는 MNIST와 같은 다른 원시 이미지 데이터셋에 비해 상대적으로 더 높은 해상도이다. 또한 이미지에 색상이 지정된다. 따라서 GPU를 사용하면 런타임에 큰 차이가 생겨 더 많은 에포크를 실행할 수 있다.

그러나 단순히 Epoch를 늘리는 것만으로는 더 나은 이미지 생성을 보장할 수 없으며 학습률이 너무 낮으면 판별자가 승리하기 시작하고 이미지 품질이 저하되기 시작한다. 모델을 개선하는 한 가지 확실한 방법은 생성기에 더 많은 레이어를 추가하는 것이다. 나는 단지 하나의 레이어로 시작했고 더 많은 레이어를 추가할 때 결과가 크게 향상되었다. 또한 다양한 유형의 활성화 함수와 최적화 함수를 실험할 수 있다. Ian Goodfellow가 직접 추천한 Adam Optimizer를 여기에서 사용했다.

식물 이미지를 생성하는 위의 예는 특히 유용하지 않을 수 있지만 동일한 기본 모델을 사용하여 예를 들어 새끼 고양이와 강아지의 이미지와 같은 다른 이미지를 생성할 수 있다. 이것은 또한 예술의 생성과 같은 GAN을 사용하는 보다 복잡한 응용 프로그램의 개발을 위한 기반을 마련한다.



## Reference

* https://github.com/carpedm20/DCGAN-tensorflow





























