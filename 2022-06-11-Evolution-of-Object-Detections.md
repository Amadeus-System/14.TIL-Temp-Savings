* **Date : 2022-06-11**
* **Last Devised : 2022-06-11**


# Evolution of Object Detection

<img src = 'https://miro.medium.com/max/994/1*gJmQdjT3YcGCcZ2H1PK7SA.gif'>

컴퓨터 비전은 상당히 발전했지만 여전히 인간지각의 정밀도를 맞추는데 어려움을 겪고 있다. 그러나 우리가 얼마나 멀리 왔는지 보는 것은 항상 좋은 일이다. 몇 년 전만 해도 매우 어려운 문제로 여겨졌던 객체감지(object detection)라고 불리는, 이미지 내에서 알 수 없는 수의 개별 객체를 감지하고 인식하는 작업이 이제 실현가능하고 [Google](https://cloud.google.com/vision/docs/drag-and-drop) 및 [IBM](https://www.ibm.com/watson/products-services)과 같은 회사에서 제품화하기도 하였다.

이번 포스팅에서는 "전통적인 객체감지 기간(traditional object detection period)(2014년 이전)"에서 "딥러닝 기반 감지 기간(deep learning based detection period)(2014년 이후)"까지 객체감지의 역사를 검토한다.


## Traditional Object Detection era

시계를 20년 전으로 돌리면 "냉기시대의 지혜(the wisdom of cold weapon era)"를 목격하게 될 것이다. 그 당시에는 효과적인 이미지 표현이 없었기 때문에 초기 객체 감지 알고리즘의 대부분은 손으로 만든 기능(handcrafted features)을 기반으로 구축되었다.


### Viola Jones Detectors

Paul Viola와 Michael Jones가 2001년에 개발한 이 객체인식 프레임워크를 사용하면 실시간으로 사람의 얼굴을 감지할 수 있다. 슬라이딩 창(sliding windows)을 사용하여 이미지에서 가능한 모든 위치와 크기(all possible locations and scales)를 통해 창에 사람의 얼굴이 포함되어 있는지 확인한다. 슬라이딩 윈도우는 본질적으로 ‘haar-like’ features을 검색한다. (haar wavelets의 개념을 개발한 Alfred Haar의 이름을 따서 명명됨)


<img src = 'https://miro.medium.com/max/542/1*GDx-HQYaCPx-LmL94L6Lgg.jpeg'>


따라서 haar wavelet은 이미지의 특징 표현으로 사용된다. 감지 속도를 높이기 위해 integral image를 사용하여 각 슬라이딩 창의 계산복잡성을 창 크기(window size)와 독립적으로 만든다. 저자는 feature selection을 위해 Adaboost 알고리즘을 사용하는 것이다. 이 알고리즘은 거대한 무작위 기능 풀 세트(a huge set of random features pools)에서 얼굴 감지에 가장 도움이 되는 작은 기능 세트를 선택한다. 알고리즘은 또한 계산량을 줄이기 위해 다단계 감지 패러다임(multi-stage detection paradigm)인 **감지 캐스케이트(Detection Cascades)**를 사용했다. 배경 창(background window)에는 계산을 덜 사용하지만 얼굴 대상에는 더 많이 사용하여 오버헤드를 줄인다.


### HOG Detector

<img src = 'https://miro.medium.com/max/652/1*P8IeGKSz3Tf1ZAjbtMD1Rg.jpeg'>

원래 N. Dalal과 B. Triggs가 2005년에 제안한 Hog는 당시의 scale invariant feature transform 및 shape contexts의 개선사항이다. HOG는 blocks(similar to a sliding window)라는 것으로 작동하는데, 그것은 하나의 dense pixel grid이고 그 안에서 그래디언트는 블록 내 픽셀 강도의 변화 크기와 방향(magnitude and direction of change in the intensities of pixels)으로 구성된다. HOG는 보행자 감지에 사용되는 것으로 널리 알려져 있다. 다양한 크기의 물체를 감지하기 위해 HOG 감지기는 감지 창의 크기(detection window)를 변경하지 않고 유지하면서 입력 이미지를 여러번 재조정(rescale)한다.


### Deformable Part-based Model (DPM)

<img src = 'https://miro.medium.com/max/1024/1*HCZiMm6PigWwR4_CpZ5FQA.jpeg'>

DPM은 원래 HOG 감지기의 확장으로 2008년 P. Felzenszwalb에 의해 제안되었다. 나중에 R. Girshick에 의해 다양한 개선이 이루어졌다. "자동차"를 감지하는 문제는 창, 차체 및 바퀴를 감지하여 '분할정복(divide and conquer)' 전략으로 나눌 수 있다. DPM은 이 전략을 사용한다. 훈련 과정에는 물체를 분해하는 적절한 방법을 배우는 것(learning a proper way of decomposing an object)이 포함되며 추론에는 서로 다른 물체 부분에 대한 앙상블 탐지(ensembling detections of different object parts)가 포함된다.

DPM 검출기는 하나의 루트 필터(root-filter)와 여러 부분 필터(a number of part-filters)로 구성된다. DPM에서는 부품 필터의 모든 구성(크기, 위치 등)(configurations(size , location etc.))을 잠재변수(latent variables)로 자동학습할 수 있는 약한 지도학습 방법이 개발되었다. 감지 정확도를 향상시키기 위해 R. Girshick은 이를 위해 특별한 경우의 다중 인스턴스 학습(Multi-Instance learning)을 사용했다. "hard negative mining", "bounding box regression" 및 "context priming"과 같은 다른 중요한 기술이 있다. 나중에 그는 정확도를 희생하지 않고도 10배 이상의 가속을 달성한 캐스케이드 아키텍처를 구현하는 기술을 사용했다.



## DeepLearning era

불행히도 객체감지는 손으로 만든 기능의 성능이 포화상태(performance of hand-crafted features became saturated)가 된 2010년 이후 안정기(plateau)에 도달했다. 그러나 2012년에, 세상은 컨볼루션 네트워크의 재탄생과 심층 컨볼루션 네트워크가 learning robust and high-level feature representations of an image에 성공적이었음을 보게 되었다.

이미지 객체 감지의 교착 상태는 객체 감지를 위한 Regions with CNN features (RCNN) 제안으로 2014년에 깨졌다. 이 딥러닝 시대에 객체감지는 "two-stage detection"와 "one-stage detection"의 2가지 장르로 그룹화된다. "단계감지"?


### RCNN

<img src = 'https://miro.medium.com/max/1400/1*iEW-FQchaOIqmrglRlJbCQ.png'>

선택적 검색(selective search)을 통해 (extraction of a set of object proposals)일련의 객체 제안(객체 후보 상자, object candidate boxes)을 추출하는 것으로 시작한다. 그런 다음 각 제안은 고정 크기 이미지로 다시 조정(rescaled to a fixed size image)되고 사전훈련된 CNN 모델에 공급되어 특징을 추출한다. 마지막으로 선형 SVM 분류기(linear SVM classifiers)가 사용되어 각 영역 내 물체의 존재를 예측하고 물체의 카테고리를 인식한다.

> RCNN은 기존(traditional) 방법보다 훨씬 우수하지만 몇 가지 단점이 있다. 많은 수의 중복 제안(overlapped proposals)(한 이미지에서 2000개 이상의 상자)에 대한 중복 특성 계산(redundant feature computations)으로 인해 감지 속도가 매우 느려진다. 또한 선택적 검색 알고리즘은 고정 알고리즘(selective search algorithm is a fixed algorithm)이다. 따라서 해당 단계에서는 학습이 일어나지 않는다. 이로 인해 잘못된 후보 지역 제안(generation of bad candidate region proposals)이 생성될 수 있다.


### SPPNet

<img src = 'https://miro.medium.com/max/1374/1*ntJDQMp56bebXsCj6C2wkg.png'>

2014년, K. He et al.은 Spatial Pyramid Pooling Networks을 제안하였다. 기존에는, 컨볼루션 계층과 완전 연결 계층이 변화되는 부분에서, 하나의 풀링 계층이 있거나 풀링 계층이 없는 경우도 있다. SPPNet에서는 스케일이 다른 다중 풀링 레이어(multiple pooling layers with different scales)를 제안한다. 또한 이전 CNN 모델에는 고정 크기 입력(fixed-size input)이 필요하다. SPPNet의 Spatial Pyramid Pooling (SPP) 레이어를 사용하면 CNN이 크기에 관계없이 고정 길이 표현(fixed-length representation)을 생성할 수 있다, 이미지의 크기나 관심영역의 리스케일링과 상관없이.


위의 다이어그램은 프로세스를 보여준다. 우리는 입력 이미지가 컨볼루션 네트워크를 사용하여 SPPNet으로 1번만 이동하는 것을 본다. 선택적 검색(Selective Search )은 R-CNN에서와 같이 영역 제안(region proposals)을 생성하는 데 사용된다. 마지막 컨볼루션 레이어에서 각각의 영역 제안에 의해 경계가 지정된 특성맵은 SPP 레이어 다음 FC 레이어로 들어간다.

> R-CNN에 비해, SPPNet은 conv layer에서 이미지를 한번만 처리하는 반면, R-CNN은 region proposal이 있는 만큼 conv layer에서 이미지를 처리한다. 그러나 다음과 같은 단점이 있다. training은 여전히 multi-stage이고 SPPNet 완전히 연결된 레이어만 미세조정하고 이전 레이어는 모두 무시한다.



### Fast RCNN

<img src = 'https://miro.medium.com/max/1268/1*b3CKrf1bIUMKlCaSTGA0VA.png'>

R-CNN 모델과 비교하여, Fast R-CNN 모델은 특성추출(feature extraction)을 위해 각각의 제안된 영역이 아닌 전체 이미지를 CNN 입력으로 사용한다. 이미지에 선택적 검색이 적용되고 n개의 제안된 영역을 생성한다고 가정한다,그것들의 다른 모양들은 다른 모양의 관심영역(Rol)을 가리킨다. Fast R-CNN은 CNN 출력과 Rol을 입력으로 사용하여 제안된 각 영역에서 추출된 특성의 연결(concatenation of the features)을 출력하고, 범주예측 동안 완전연결계층에 공급하는 RoI pooling을 도입한다. 범주 예측 중에 완전연결계층 출력의 모양은 다시 $n x q$로 변환되고, softmax 회귀를 사용한다(q는 범주의 수이고 n은 제안된 영역의 수이다). 경계상자 예측(bounding box prediction) 동안, 완전히 연결된 레이어 출력의 모양은 다시 $n \times 4$ 로 변환된다. 이는 우리가 각각의 제안된 영역에 대해 바운딩 박스와 카테고리를 예측함을 의미한다.

"Fast R-CNN"이 R-CNN보다 빠른 이유는 매번 모든 영역 제안(all region proposals )을 컨볼루션 신경망에 제공할 필요가 없기 때문이다. 대신 이미지당 1번만 컨볼루션 작업이 수행되고 이미지에서 특성맵이 생성된다.

> Fast-RCNN은 R-CNN과 SPPNet의 장점을 성공적으로 통합했지만 탐지속도는 여전히 제안 탐지(proposal detection)에 의해 제한된다.


### Faster RCNN

<img src = 'https://miro.medium.com/max/1268/1*-BrpDpmOJc2zp7y1d0w5fw.png'>

2015년 S. Ren et al.은 Fast RCNN 이후 얼마 지나지 않아 Faster RCNN을 제안했다. Faster FCNN 검출기는 최초의 end-to-end이자 최초의 거의 실시간 딥러닝 객체 검출기이다. 위의 모든 알고리즘들(R-CNN, SPPNet & Fast RCNN)은 지역 제안을 찾기 위해 selective search를 사용한다. 선택적 검색은 네트워크 성능에 영향을 미치는 느리고 시간 소모적인 프로세스이다. Faster R-CNN은 선택적 검색 알고리즘을 제거하고 네트워크가 지역 제안을 학습하도록 한다.

Fast R-CNN과 유사하게, 이미지는 Convolutional Feature map을 제공하는 Convolutional Network에 대한 입력으로 제공된다. 지역 제안을 식별하기 위해 특성맵에서 선택적 검색 알고리즘을 사용하는 대신, 지역 제안을 예측하기 위해 하나의 분리된 네트워크가 사용된다. 예측된 영역 제안은 그런 다음 제안 영역 내에서 이미지를 분류하고 경계상자에 대한 오프셋 값을 예측하는 데 사용되는 Rol 풀링 레이어를 사용하여 재구성된다.

Faster R-CNN 모델의 일부로, 지역 제안 네트워크(region proposal network)는 모델의 나머지 부분과 함께 훈련된다. 또한 Faster R-CNN 목적함수에는 객체탐지에서의 범주 및 경계상자 예측과 지역제안 네트워크의 앵커 상자에 대한 범주 및 경계상자 예측이 포함된다. 마지막으로 지역 제안 네트워크는 객체탐지의 정밀도를 유지하면서 제안된 지역의 수를 줄이는 고품질 제안지역을 생성하는 방법(how to generate high-quality proposed regions)을 학습할 수 있다.

> Faster RCNN이 Fast RCNN의 속도 병목현상을 극복했지만, 후속 감지 단계에서 여전히 계산중복이 있다. 나중에 RFCN 및 Light Head RCNN을 포함한 다양한 개선 사항이 제안되었다.



### Feature Pyramid Networks (FPN)

<img src = 'https://miro.medium.com/max/538/1*r5OeVqonKzuf9LLHtxHGwg.jpeg'>

2017년, T.-Y. Linet al.은 Feature Pyramid Networks를 제안했다. Faster RCNN을 살펴보면, 대부분 이미지에서 작은 개체를 포착할 수 없다는 것을 알 수 있다. 이 문제를 해결하기 위해 간단한 이미지 피라미드를 사용하여 이미지를 다양한 크기로 확장하고 네트워크로 보낼 수 있다. 각각의 스케일에서에서 탐지가 감지되면, 모든 예측을 다른 방법들을 사용하여 결합할 수 있다.

FPN 이전에는, 대부분의 딥러닝 기반 감지기가 네트워크의 최상위 계층에서만 감지를 실행한다. CNN의 더 깊은 레이어에 있는 특성들은 카테고리 인식에 유용하지만, 객체를 지역화(localizing objects)하는 데 도움이 되지 않는다. FPN에서는 측면 연결이 있는 하향식 아키텍처( topdown architecture with lateral connections)가 개발되어 모든 규모에서 높은 수준의 의미 체계(high-level semantics at all scales)를 구축한다. CNN은 순방향 전파를 통해 자연스럽게 피처 피라미드를 형성하기 때문에, FPN은 다양한 스케일로 객체를 감지하는데 큰 발전을 보여준다.

> FPN은 이제 많은 최신 탐지기의 기본 빌딩 블록이 되었다.


### You Only Look Once (YOLO)

<img src = 'https://miro.medium.com/max/1268/1*7O_2t_ZFDHd1CRpWaEJH_w.jpeg'>

이전의 모든  object detection algorithm은 영역을 사용하여 이미지 내에서 물체를 지역화(localize)했다. 네트워크는 전체 이미지를 보지 않고 대신 객체를 포함할 가능성이 높은 이미지 부분을 본다.

YOLO는 전체 이미지에 대해 학습하고 감지 성능을 직접 최적화한다. YOLO를 사용하면, 단일 CNN이 여러 경계상자와 해당 상자에 대한 클래스 확률을 동시에 예측한다. 또한 이미지에 대한 모든 클래스의 모든 경계상자를 동시에 예측한다. 그것은 입력 이미지를 $S \times S$ 그리드로 나눈다. 객체의 중심이 그리드 셀에 떨어지면, 해당 그리드 셀이 해당 객체를 감지하는 것과 관련이 있다. 각 그리드 셀은 B 경계상자와 해당 상자에 대한 신뢰도 점수(confidence score)를 예측한다. 이러한 신뢰도 점수는 모델이 상자에 객체가 포함되어 있다는 확신과 예측한 상자가 얼마나 정확하다고 생각하는지를 반영한다.

각 경계상자는 6개의 숫자(pc, bx, by, bh, bw, c)로 표시된다. 여기서 pc는 경계상자에 있는 개체의 신뢰도(confidence)이고 bx, by, bh, bw는 경계상자 자체를 나타낸다. c는 클래스 확률을 포함하는 벡터이다. 또한 교육 데이터를 탐색하여 다양한 클래스를 나타내는 합리적인 높이/너비 비율을 선택하여 **앵커상자(Anchor boxes)**를 정의한다. 앵커 상자에는 여러 경계상자가 있을 수 있다. 각 앵커상자(각 그리드 셀의) 요소별 곱(element-wise product) pc * c[i]를 계산하고 특정 클래스를 포함하는 상자의 확률 점수를 추출한다. 최대 점수와 관련된 클래스는 점수 자체와 함께 앵커상자에 할당된다.

그런 다음 확률 점수의 임계값을 사용하여 점수가 낮은 상자를 제거할 수 있다. 그러나 여전히 많은 상자를 얻는다. 따라서 우리는 Non-maxima suppression(비극대값 억제, NMS)라는 것을 사용하는데, 이 과정에서 우리는 여러 상자가 서로 겹쳐있을 때 하나의 상자만을 선택하고, 같은 객체를 탐지한다.

> YOLO는 감지 속도가 크게 향상되었음에도 불구하고 특히 일부 작은 물체의 경우 2단계 감지기에 비해 위치 정확도가 떨어지는 문제가 있다. YOLO의 후속버전(YOLO V2, YOLO V3 및 최신 YOLO V4)과 후자의 제안된 SSD(Single Shot MultiBox Detector)는 이 문제에 더 많은 관심을 기울였다.


### Single Shot MultiBox Detector (SSD)

<img src = 'https://miro.medium.com/max/626/1*JVq-XWgS1kyVVbUL0FZpXQ.jpeg'>

SSD는 2015년 WW. Liu et al.에 의해 제안되었다. 그 후 2016년 11월에 [SSD: Single Shot MultiBox Detector](https://arxiv.org/abs/1512.02325?source=post_page)에 대한 논문이 C. Szegedy et al.에 의해 발표되었는데, 객체감지 작업의 성능과 정밀도(precision) 측면에서 새로운 기록을 달성했다. 그것은 yolo와 같은 one-step 객체감지기이다. SSD의 주요 기여는 다중 참조(multi-reference) 및 다중 해상도(multi-resolution) 감지 기술의 도입으로, 특히 일부 작은 물체에 대해 1단계 감지기의 감지 정확도를 크게 향상시킨다. YOLO 및 Faster RCNN 이후에 발표된 이 문서는 $300 \times 300$ 입력 크기 이미지에 대해 59fps에서 74.3mAP를 달성한다. 이 네트워크는 SSD300이라 불린다. 유사하게 SSD512는 Faster R-CNN 결과를 능가하는 76.9mAP를 달성한다.

그것은 기본 네트워크(Base network)로 시작하여 특성맵을 추출한다. 표준 사전훈련된 네트워크는 고품질 이미지 분류(high quality image classification)에 사용되며 분류 계층 전에 잘린다. 그들의 논문에서, C. Szegedy et al. VGG16 네트워크를 사용했다. VGG19 및 ResNet과 같은 다른 네트워크를 사용할 수 있으며 좋은 결과를 생성해야 한다. 그런 다음 일련의 컨볼루션 필터인 **다중 스케일 피처 레이어(Multi-scale feature layers)**가 기본 네트워크 뒤에 추가된다. 이러한 레이어는 크기가 점진적으로 감소하여 여러 스케일에서 탐지를 예측하는 것을 허용한다. 그런 다음 Non-maximum suppression이 사용되어 겹치는 상자를 제거하고 탐지된 각 개체에 대해 하나의 상자만 유지한다.


### RetinaNet

<img src = 'https://miro.medium.com/max/572/1*vPQEf1JXMRBmwbVQCXVW0w.jpeg'>

조밀한 1단계 검출기의 훈련 중에 극단적인 클래스 불균형 문제(extreme class imbalance problem)가 있음이 발견되었다. 그리고 이것이 빠른 속도와 단순성에도 불구하고 1단 검출기의 성능이 **2단 검출기보다 열등한** 주요 원인(central cause)으로 여겨진다. "초점 손실(focal loss)"이라는 새로운 손실함수가 RetinaNet에 도입되었다. 낮은 손실은 "쉬운" 네거티브 샘플로 인해 감지기가 훈련중에 어렵고 잘못 분류된 예에 더 집중할 수 있도록 한다. 초점 손실을 사용하면 1단계 감지기가 매우 높은 감지 속도를 유지하면서 2단계 감지기에 필적하는 정확도를 달성할 수 있다.


특성추출을 위한 중추망(backbone)으로서 ResNet + FPN에, 분류와 경계상자 회귀를 위한 2개의 작업별 서브네트워크를 더하여, RetinaNet은 최첨단 성능을 달성하고 Faster R-CNN과 같은 잘 알려진 2단계 검출기를 능가한다.

> 지금은 여기까지이다.


우리는 컴퓨터 비전에서 매우 어렵고 매우 복잡하며 고도로 진화하는 영역인 물체 감지의 진화에 대해 간략하게 논의했다. 매년 새로운 알고리즘이 이전 알고리즘보다 성능이 계속 향상되고 있다. 오늘날, 객체감지를 위한 사전훈련된 모델들이 매우 많이 있다. 또한 물체감지는 물체추적(Tracking objects)(축구 월드컵에서 경기 중 공 추적 등), 자동 CCTV 감시(Automated CCTV surveillance), 사람 감지(Person Detection)(지능형 비디오 감시 프레임워크에 사용), Vehicle Detection 등을 비롯한 많은 흥미로운 분야에서 응용 프로그램을 발견했다.  그것은 또한 현대 시대의 가장 흥미롭고 매우 기대되는 혁신 중 하나인 자율 주행(autonomous driving)에 적용되었다.


## Reference

* https://medium.com/analytics-vidhya/evolution-of-object-detection-582259d2aa9b
    - Object Detection in 20 Years: A Survey → https://arxiv.org/pdf/1905.05055.pdf
    - RCNN → https://arxiv.org/pdf/1311.2524.pdf
    - Fast RCNN → https://arxiv.org/pdf/1504.08083.pdf
    - Faster RCNN → https://arxiv.org/pdf/1506.01497.pdf
    - Yolo → Coursera DeepLearning Specialization by Andrew Ng.
    - HOG → https://www.learnopencv.com/histogram-of-oriented-gradients/
    - SSD → https://arxiv.org/abs/1512.02325
    - FPN → https://jonathan-hui.medium.com/understanding-feature-pyramid-networks-for-object-detection-fpn-45b227b9106c
    - SPPNet → https://arxiv.org/abs/1406.4729










































