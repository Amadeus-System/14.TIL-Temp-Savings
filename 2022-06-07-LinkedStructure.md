

# Chapter 6. 연결된 구조

## 6.1 연결된 구조란?

### 연결된 구조는 흩어진 데이터를 링크로 연결해서 관리한다.

많은 자료를 저장하고 관리하기 위해 **배열구조**나 **연결된 구조**를 사용할 수 있다는 것은 공부했지만, 지금까지는 리스트, 스택, 큐, 덱 등 모든 자료구조를 배열 구조로 구현하였다. 이제 연결된 구조로 자료구조를 표현하는 방법을 알아보자.

**배열 구조**의 가장 큰 특징은 모든 항목들을 **연속된 메모리 공간**에 저장하는 것인데, 연결된 구조에서는 이와 같이 데이터를 한 곳에 모아두는 것을 포기한다. 즉, 항목들이 메모리상에서 여기저기 흩어져서 존재할 수 있다. 그렇다면 어떻게 흩어진 데이터를 모아서 관리할 수 있을까? **링크(Link)**를 이용한다. 즉, 항목들이 다른 항목을 가리키는 하나 이상의 링크(그림에서 상자에 연결된 줄)를 갖도록 하여 전체 항목들이 하나로 연결되도록 하는 것이다.

이와 같이 항목들을 링크로 연결하여 표현하는 방법을 **연결된 구조(Linked Structure)**라 한다. 특히 항목들을 링크를 통해 **일렬로 나열할 수 있는 연결된 구조**를 **연결 리스트(Linked List)**라 부른다. 그림에서 하나의 상자를 **노드(Node)**라고 하는데, **데이터**와 함께 **링크**를 갖는다. 연결된 구조에서 링크의 수를 늘리면 선형자료구조 뿐 아니라 트리나 그래프와 같이 더 복잡한 구조도 효율적으로 표현할 수 있다. 그렇지만 배열 구조에서와 같이 한번에 $k$번째 항목의 주소를 계산해서 바로 찾아갈 수 없음에 유의하라. 시작 항목에서부터 링크를 따라 각 항목을 하나씩 찾아갈 수 밖에 없다. 모든 것에는 장점과 단점이 있다.


![그림6 1](https://user-images.githubusercontent.com/76824867/172344443-5eaa520b-5e9d-4848-bd9b-e0e0b801cbc3.PNG)

[그림 6.1] 배열 구조와 연결된 구조의 비교



### 배열 구조와 연결된 구조의 장단점

* 배열 구조와 달리 연결된 구조는 **용량이 고정되지 않는다**. 즉 필요한 것만 필요할 때 만들어 쓰기 때문에 메모리를 효율적으로 사용한다. 또한 컴퓨터에 메모리가 남아 있는 한 계속 자료를 넣을 수 있다.

![그림6 2](https://user-images.githubusercontent.com/76824867/172344452-db3f0e9e-9b6e-47c8-808e-a4db6e597cdf.PNG)

[그림 6.2] 연결된 구조에서는 용량이 고정되지 않는다.



* 중간에 자료를 **삽입하거나 삭제하는 것이 용이**하다. 파이썬의 리스트와 같은 배열 구조에서는 많은 항목들의 이동이 필요함을 기억하라. 연결된 구조에서는 그림과 같이 링크만 수정하면 되므로 시간복잡도가 $O(1)$이다.


![그림6 3](https://user-images.githubusercontent.com/76824867/172344453-d4b5122d-d163-4465-ba8e-d9090c6b2a36.PNG)

[그림 6.3] 연결된 구조에서는 중간에 데이터를 삽입하거나 삭제하는 것이 용이하다.


* 연결된 구조에서는 **$n$번째 항목에 접근하는데 $O(n)$의 시간이 걸린다**. 이것은 배열 구조의 $O(1)$과 비교하면 큰 단점이다. 또한 배열에 비해 상대적으로 구현이 어렵고 오류가 발생하기도 쉽다.


### 연결 리스트의 구조

#### 노드(Node)

그림의 연결된 구조에서 하나의 상자는 컴퓨터 용어로 **노드(Node)**라고 한다. 배열 구조에서 각 항목들은 데이터만을 갖는 것과 달리 노드는 **데이터 필드(Data Field)**와 함께 **하나 이상**의 **링크 필드(Link Field)**를 갖는다. 연결 리스트의 대표적인 노드 구조는 다음과 같다.

![그림6 4](https://user-images.githubusercontent.com/76824867/172344455-37af087b-13b3-46de-8dd2-94da760f5897.PNG)

[그림 6.4] 연결된 구조에서의 노드 구조



**데이터 필드**에는 우리가 저장하고 싶은 데이터가 들어간다. 이것은 정수가 될 수도 있고 복잡한 클래스의 객체나 심지어 다른 리스트도 될 수 있다. **링크 필드**는 다른 노드를 **가리키는**, 즉 다른 노드의 **주소를 저장하는 변수**이다. 이것을 이용해 연결된 다음 노드에 접근할 수 있다. 배열에 비해 링크를 위한 약간의 추가 공간이 필요하지만, 대부분의 경우 데이터 필드가 훨씬 크므로 링크를 위한 공간은 무시할 수 있다.



#### 헤드 포인터(Head Pointer)

연결 리스트는 첫번째 노드만 알면 링크로 매달려 있는 모든 노드에 순차적으로 접근할 수 있다. 따라서 시작 노드의 주소를 반드시 저장해야 한다. 연결 리스트에서 첫번째 노드의 주소를 저장하는 변수를 헤드 포인터(Head Pointer)라고 한다. 마지막 노드는 더 이상 연결할 노드가 없다. 따라서 링크의 값을 None으로 설정하여 이 노드가 마지막임을 표시한다.

![그림6 5](https://user-images.githubusercontent.com/76824867/172344458-ec3f643a-fa1e-4deb-b047-ae42f2575201.PNG)

[그림 6.5] 연결된 구조에서의 시작 노드의 주소를 잘 관리해야 한다.



포인터(Pointer)는 다른 객체를 **가리키고(Pointing) 있는 변수**라는 의미이다. C나 C++ 등에서는 포인터의 개념이 매우 중요하게 사용되고 있고, 이들 언어 측면에서 보면 파이썬의 모든 변수는 **포인터나 참조자(Reference)**와 같은 의미로 사용된다고 볼 수 있다. 그렇지만 파이썬에서 메모리의 해제와 같은 포인터와 관련된 번거로운 작업들이 자동으로 처리되기 때문에 부담없이 포인터를 그냥 변수로 생각하고 사용하면 된다.



### 연결 리스트의 종류

#### 단순연결리스트(Singly Linked List)

하나의 방향으로만 연결되어 있는 구조를 갖는다. 따라서 링크는 하나이며, 이 변수는 다음 노드의 주소를 기억하고 있다. 마지막 노드의 링크는 아무것도 연결되어 있지 않다는 것을 나타내기 위해 반드시 None 값을 가져야 한다는 것을 명심하라. 6.2와 6.3절에서 **스택**과 **리스트**를 단순연결리스트로 다시 구현해 볼 것이다.

![그림6 6](https://user-images.githubusercontent.com/76824867/172344461-ac7a5a7d-61a5-4f9a-a04a-56b95a208f34.PNG)

[그림 6.6] 단순연결리스트의 구조



#### 원형연결리스트(Circular Linked List)

단순연결리스트와 동일한 노드 구조를 사용하지만 맨 마지막 노드의 링크 값이 None이 아니라 다시 첫번째 노드를 가리킨다는 것이 다르다. 따라서 노드들을 순서대로 방문할 때 **종료조건**에 유의해야 한다. 6.4절에서 **큐**를 원형연결리스트로 다시 구현해보자.

![그림6 7](https://user-images.githubusercontent.com/76824867/172344463-3521b904-5950-496e-8ed5-270d5a37b9f6.PNG)

[그림 6.7] 원형연결리스트의 구조



#### 이중연결리스트(Doubly Linked List)

하나의 노드가 이전 노드와 다음 노드를 모두 알고 있도록 설계되었다. 따라서 2개의 링크를 갖는데, 하나는 **선행 노드(Previous Node)**를 다른 하나는 **후속 노드(Next Node)**를 가리킨다. 이중연결리스트의 노드 구조는 다음과 같다.

![그림6 8](https://user-images.githubusercontent.com/76824867/172344465-3e2ea4d1-4362-4e97-afb6-049b7866b84a.PNG)

[그림 6.8] 이중연결리스트에서의 노드의 구조



선행 노드를 위한 링크가 있으면 어떤 노드에서 이전 노드를 바로 찾아갈 수 있다는 장점이 있다. 편리한 만큼 이중으로 링크를 정확히 유지해야 하기 때문에 코드가 복잡해진다. 6.5절에서 덱을 이중연결리스트로 구현해 볼 것이다.

![그림6 9](https://user-images.githubusercontent.com/76824867/172344467-f2c59155-5b87-4eb6-a90c-8fd7b533865a.PNG)

[그림 6.9] 이중연결리스트의 구조



## 6.2 단순연결리스트 응용 : 연결된 스택

단순연결리스트로 스택을 구현하자. 이러한 스택을 **연결된 스택(Linked Stack)**이라 한다. 스택은 입출력이 상단으로 제한되는 자료구조이다. 4장에서 배열 구조로 스택을 구현하였다. 이때 top은 파이썬의 리스트를 가리켰으며, 삽입과 삭제 연산은 리스트인 top의 후단을 통해 이루어졌다.

단순연결리스트 구조의 연결된 스택에서는 무엇을 top으로 사용해야 할까? 단순연결리스트의 **헤드 포인터를 스택의 top**으로 사용하면 된다. 모든 자료의 입출력이 top을 통해 가능하므로 추가적인 변수도 필요없다. 이와 같이 연결된 스택은 **단순연결리스트의 가장 간단한 응용**이다. 스택의 구현 방법이 달라지더라도 사용 방법은 동일하다. 따라서 연결된 스택을 4장에서 공부한 스택의 테스트 코드에 그대로 활용할 수 있다.


![A1](https://user-images.githubusercontent.com/76824867/172344414-f636d740-3e89-49ee-8726-0dd28cee41b6.PNG)


### 클래스 정의

연결된 스택을 위해서는 노드와 스택 클래스를 각각 구현해야 한다. 먼저 노드 클래스를 구현하자. 단순연결리스트를 위한 노드는 데이터 필드와 하나의 링크만 있으면 되고, 이들은 생성자에서 선언 및 초기화된다. 다음 코드는 Node 클래스의 구현을 보여주는데, 링크는 디폴트 인수 기능을 이용해 인수가 전달되지 않으면 None으로 초기화하도록 하였다.

``` Python
class Node():                                   # 단순연결리스트를 위한 노드 클래스
    def __init__(self, elem, link = None):      # 생성자, 디폴트 인수 사용
        self.data = data                        # 데이터 멤버 생성 및 초기화
        self.link = link                        # 링크 생성 및 초기화
```

C++나 Java 등과는 달리 생성자의 매개변수로 데이터 멤버와 같은 이름을 사용해도 문제가 없다. 왜냐하면 **클래스의 모든 멤버는 self를 통해 접근**해야 하기 때문이다. 예를 들어, 위의 코드에서 **link는 매개변수**이고, **self.link**는 **데이터 멤버**이다. 이들은 정확히 구별되기 때문에 파이썬에서는 멤버와 같은 이름의 매개변수를 많이 사용한다.

스택 클래스의 이름은 LinkedStack 이라 하자. **데이터 멤버**로는 **시작노드를 가리키는 변수 top**만 있으면 된다. 4장에서는 top을 배열(파이썬의 리스트)로 사용하였다. 맨 처음에는 top이 None으로 초기화되어야 하고, 따라서 연결된 스택의 공백상태는 top이 None을 가리키는 경우이다. 스택의 초기화는 스택을 공백상태로 만드는 것이므로 top이 None을 가리키도록 하면 된다. 클래스 정의와 이들 멤버 함수의 구현은 다음과 같다.

``` Python
class LinkedStack():
    def __init__(self):             # 생성자
        self.top = None             # top 생성 및 초기화
    
    def isEmpty(self):
        return self.top == None     # 공백상태 검사
    def clear(self):
        self.top = None             # 스택 초기화
```


#### push(E): 삽입 연산

배열 구조에서와는 달리 연결된 스택에서는 삽입할 데이터를 직접 스택에 넣을 수 없다. 먼저 데이터를 넣을 **새로운 노드를 만들고, 이 노드를 스택의 top에 추가**해야 한다. 전체 삽입 연산은 다음과 같이 3단계로 이루어진다.

1. 입력 데이터 E를 이용해 새로운 노드 $n$을 생성함 : $n = Node(E)$
2. $n$의 링크가 시작노드를 가리키도록 함 : n.link = top
3. top이 n을 가리키도록 함 : top = n


![그림6 10](https://user-images.githubusercontent.com/76824867/172344470-7c370543-9c29-4ebd-950e-ae48eeceaa04.PNG)

[그림 6.10] 연결된 스택에서의 삽입 과정



실제 구현 코드에서는 Node의 생성자를 이용하여 데이터와 링크를 동시에 (단계 1과 2를 한번에 처리) 초기화할 수 있다. 코드는 다음과 같다.

``` Python
    def push(self, item):           # 연결된 스택의 삽입연산
        n = Node(item, self.top)    # Step 1 + Step 2
        self.top = n                # Step 3
```


#### pop() : 삭제 연산

삭제는 상단 항목을 꺼내서 반환하는 연산이다. 연결된 구조에서는 **top이 가리키는 노드를 꺼내고 데이터 필드만을 반환**하면 된다. 이 과정은 다음과 같다.

1. 변수 n이 시작노드를 가리키도록 함 : n = top
2. top이 다음 노드를 가리키도록 함 : top = n.link
3. n이 가리키는 노드의 데이터를 반환함 : return n.data



![그림6 11](https://user-images.githubusercontent.com/76824867/172344472-6efc3b30-44f1-47c6-b8b2-99e700319d87.PNG)

[그림 6.11] 연결된 스택에서의 삭제 과정



코드는 다음과 같다. 공백상태를 반드시 검사해야 하는 것에 유의하라. 공백이 아니면 top이 가리키는 노드를 꺼내고 데이터 필드를 반환한다. 4장의 배열 구조로 구현한 스택에서와 같이 **노드가 아니라 스택 항목을 반환함**에 유의하라.

``` Python
    def pop(self):                  # 연결된 스택의 삭제연산
        if not self.isEmpty():      # 공백이 아니면
            n = self.top            # Step 1
            self.top = n.link       # Step 2
            return n.data           # Step 3
```

연결된 구조에서 삭제 연산으로 꺼낸 노드의 메모리를 프로그래머가 직접 해제할 필요가 없음에 유의하라. 예를 들어, 위의 그림에서 노드 A를 삭제하는 코드가 필요없다. 파이썬에서는 어떤 **객체를 참조하는 변수가 하나도 없으면 그 객체는 자동으로 삭제**된다. C나 C++에서 포인터와 관련하여 프로그래머를 괴롭히던 메모리 관리라는 큰 골칫거리 하나가 사라졌다.



#### peek()

peek는 시작노드의 데이터를 반환하면 된다. 물론 공백상태이면 안 된다.

``` Python
    def peek(self):                 # 연결된 스택의 peek 연산
        if not self.isEmpty():      # 공백이 아니면
            return self.top.data    # 시작 항목의 데이터 반환
```


#### size()

연결된 구조에서는 스택의 항목 수를 구하기가 어렵다. 왜냐하면 링크를 따라 맨 마지막 노드까지 움직여보기 전에는 몇 개의 노드들이 매달려 있는지 알 수 없기 때문이다. 마지막 노드는 링크가 None인 노드이다. 시작 노드에서부터 전체 노드를 순회하여 노드의 개수를 구하는 방법은 다음 그림과 같다. 배열 구조(파이썬 리스트)를 사용할 때에는 리스트의 크기를 반환하는 함수 len()을 호출하면 되었던 것을 기억하라. 연결된 구조에서는 이렇게 할 수 없다.

![그림6 12](https://user-images.githubusercontent.com/76824867/172344474-7ef908f9-de6a-4d26-b317-1ea7dffd1d33.PNG)

[그림 6.12] 연결된 구조에서의 순차적인 노드 방문 과정


``` Python
    def size(self):                 # 스택의 항목 수 계산
        node = self.top             # 시작 노드
        count = 0
        while not node == None:     # node가 None이 아닐 때까지
            node = node.link        # 다음 노드로 이동
            count += 1              # count 증가
        return count                # count 반환
```


스택 클래스에 노드의 개수를 저장하는 count와 같은 데이터 멤버를 추가하면 좋을 것처럼 보인다. 그러나 이 경우 삽입연산이나 삭제 연산에서 count를 정확히 관리해주어야 하는 문제가 있다. **변수를 많이 사용하면 편리**한 점이 있다. 그러나 반드시 모든 함수에서 이들을 **일관성 있게 관리해야 한다는 부담**이 따른다.



#### display()

size() 연산에서의 노드 방문 방법은 스택 내용을 모두 출력할 때에도 동일하게 적용된다. 모든 노드의 데이터를 출력하기 위해서는 모든 노드들을 방문해야 하기 때문이다. 다음은 연결된 구조에서 시작노드부터 순서대로 마지막 노드까지 방문하는 전형적인 코드이다.

``` Python
    def display(self, msg = 'LinkedStack :'):   # 스택의 항목 출력 함수
        print(msg, end = '')                    # 메시지를 먼저 출력
        node = self.top                         # 시작 노드
        while not node == None:                 # node가 None이 아닐 때까지
            print(node.data, end = ' ')         # node의 데이터 멤버 출력
            node = node.link                    # 다음 노드로 이동
        print()
```

연결된 스택의 테스트에는 4장에서 사용한 코드를 그대로 사용하자. 2개의 스택 객체를 만드는 코드는 다음과 같이 수정되어야 한다. 출력은 print() 함수가 아니라 display() 메소드를 이용한다.

``` Python
odd  = LinkedStack()    # 홀수 저장을 위한 연결된 스택
even = LinkedStack()    # 짝수 저장을 위한 연결된 스택
```

실행 결과는 4장과 동일한데, 스택의 출력은 가장 최근에 삽입된 항목부터이다. 즉, 4장에서 슬라이싱을 이용해 리스트를 역순으로 뒤집은 경우의 출력과 같다. 이것은 구현된 스택의 display() 연산이 가장 최근 노드부터 방문하기 때문이다.


#### 연결된 스택의 시간복잡도 분석

연결된 스택의 삽입과 삭제 연산의 시간복잡도도 $O(1)$이다. 그러나 배열 구조에서 파이썬의 리스트가 **용량을 증가**시켜야 하는 상황이 발생하면 $O(n)$의 시간이 걸릴 수 있는 점을 감안한다면 연결된 스택이 더 유리하다. size는 배열에서는 $O(1)$이지만 연결된 스택에서는 $O(n)$이다. 물론 크기를 위한 변수를 하나 추가하고, 삽입과 삭제 연산에서 이 변수를 잘 관리한다면 $O(1)$이 될 수 있다. 연습문제 6.2에 도전하라.




## 6.3 단순연결리스트 응용 : 연결된 리스트

스택과는 달리 리스트는 항목의 삽입이나 삭제가 시작노드뿐만 아니라 임의의 위치에서도 가능하다. 스택보다 기능이 많으니 코드도 스택보다는 복잡해질 것이다. 3장에서 배열로 구현한 리스트를 연결된 구조로 다시 구현해보자.


![A2](https://user-images.githubusercontent.com/76824867/172344429-1dc3c247-7f3f-49b7-8269-710d6a895670.PNG)



리스트 ADT를 구현하기 위해 더 복잡한 연결구조를 사용할 수도 있지만, 여기서는 단순연결리스트를 사용한다. 다음과 같이 변수 head가 시작 노드를 가리키도록 하고, 마지막 노드의 링크는 None을 갖는다.

![그림6 13](https://user-images.githubusercontent.com/76824867/172344477-e29b11d4-9bc1-400c-bf27-9e82f5252186.PNG)

[그림 6.13] 연결된 리스트의 구조


### 클래스 정의

노드는 연결된 스택에서와 완전히 동일하므로 같은 코드를 사용한다. 연결된 리스트 클래스의 이름은 LinkedList 라고 하자. **데이터 멤버**는 **헤드 포인터**인 **head**만으로 충분하다. 공백상태는 스택에서와 동일한데, head가 None인지를 검사하면 된다. 리스트의 초기화도 self.head = None 이면 충분하다. 클래스 정의와 이들 멤버함수의 구현은 다음과 같다.

``` Python
class LinkedList():                 # 연결된 리스트 클래스
    def __init__(self):
        self.head = None

    def isEmpty(self):              # 공백상태 검사
        return self.head = None

    def clear(self):                # 리스트 초기화
        self.head = None

    def size(self):                 # self.top -> self.head로 수정. 코드 동일
        pass

    def display(self, msg):         # self.head 및 출력형식 약간 수정
        pass
```

리스트 항목의 수를 반환하는 size 연산과 내용을 출력하는 display 연산은 연결된 스택에서와 정확히 같은 방법을 사용한다. 앞의 코드에서 시작 노드를 가리키는 변수를 self.top에서 self.head로 변경하기만 하면 된다.


### getNode(pos) : 새로운 연산 추가

리스트 ADT에 없는 연산을 추가하자. pos번째 노드를 반환하는 연산이다. 배열구조에서는 "노드"의 개념이 없으니 이 연산은 의미가 없다. 연결된 구조에서는 노드를 사용하기 때문에 pos번째 노드를 반환하는 연산 getNode(pos)가 필요하다. 어떻게 pos번째 노드를 찾을 수 있을까? head부터 시작하여 링크를 따라 순서적으로 찾아가서 해당 노드를 반환하면 된다. getNode의 시간복잡도가 $O(n)$인 것에 유의하라. pos번 움직여야 원하는 노드에 접근할 수 있다.

``` Python
    def getNode(self, pos):                 # pos번째 노드 반환
        if pos < 0:
            return None
        node = self.head                    # node는 head부터 시작
        while pos > 0 and node != None:     # pos번 반복
            node = node.link                # node를 다음 노드로 이동
            pos -= 1                        # 남은 반복 횟수 줄임
        return node                         # 최종 노드 반환
```


### getEntry(pos), replace(pos, elem), find(val)

getNode 연산이 구현되면 항목의 데이터만을 반환하는 getEntry를 다음과 같이 간단하게 구현할 수 있다.

``` Python
    def getEntry(self, pos):        # pos번째 노드의 데이터 반환
        node = self.getNode(pos)    # pos번째 노드
        if node == None:            # 찾는 노드가 없는 경우
            return None
        else:                       # 그 노드의 데이터 필드 반환
            return node.data
```

이 연산의 시간복잡도는? 배열로 구현했을 때에는 $O(1)$이었다. 연결된 리스트에서는 getNode가 $O(n)$이므로 이 연산도 $O(n)$이 된다. 이것은 배열에 비해 매우 비효율적이지만, 항목들이 메모리에 흩어져 있기 때문에 다른 방법이 없다. 항상 장점이 있으면 단점이 있기 마련이다.

어떤 위치의 항목을 다른 데이터로 변경하는 replace 연산은 getNode를 이용해 간단히 구현할 수 있다.

``` Python
    def replace(self, pos, elem):   # pos번째 노드의 데이터를 변경
        node = self.getNode(pos)    # pos번째 노드를 찾아
        if node != None:
            node.data = elem        # 데이터 필드에 elem 복사
```

원하는 데이터를 가진 노드를 찾는 함수도 비교적 간단하다. head부터 연결된 노드를 하나씩 방문하면서 검사하면 되기 때문이다.

``` Python
    def find(self, data):           # 데이터로 data를 찾는 노드 반환
        node = self.head
        while node is not None:     # 모든 노드에서 찾음
            if node.data == data:   # 찾아지면 바로 반환
                return node
            node = node.link
        return None                 # 찾아지지 않으면 None 반환
```


### insert(pos, elem) : 삽입 연산

다음은 단순연결리스트에서 임의의 위치에 노드를 삽입하는 과정을 보여준다. 삽입 결과를 보면 pos 위치의 노드가 아니라 그 이전노드 before의 링크 값이 수정되는 것에 유의하라. 즉, pos 위치에 새로운 노드를 삽입하려면 그 노드의 선행노드를 알아야 한다.


![그림6 14](https://user-images.githubusercontent.com/76824867/172344479-34a01460-420c-4975-b3d4-110c4a0e4a2b.PNG)

[그림 6.14] 단순연결리스트의 삽입연산


1. 노드 N이 노드 C를 가리키게 함 : node.link = before.link
2. 노드 B가 노드 N을 가리키게 함 : before.link = node

이 연산의 시간복잡도는 어떻게 될까? 만약 before를 알고 있다면 두 단계만에 처리되고, 따라서 $O(1)$이다. 배열구조를 이용한 경우는 위치를 알더라도 항목의 이동을 위해 $O(n)$이 필요한 것을 기억하라. 이것이 연결리스트의 장점이다.

만약 before를 모르고 삽입할 위치의 노드만 알고 있다면 어떻게 될까? 단순연결리스트의 노드에는 선행노드에 대한 정보가 없다. 따라서 시작노드부터 하나씩 다시 검사해야 한다. 이것은 before를 찾기 위해 $O(n)$의 시간이 필요한 것을 의미한다. 삽입 연산에서 **맨 앞에 노드를 삽입하는 경우**는 멤버 변수인 head가 변경되어야 하므로 다음 코드와 같이 특별하게 처리해주어야 한다.

``` Python
    def insert(self, pos, elem):                
        before = self.getNode(pos - 1)          # before 노드를 찾음
        if before = None:                       # 맨 앞에 삽입하는 경우
            self.head = Node(elem, self.head)   # 맨 앞에 삽입함
        else:                                   # 중간에 앞에 삽입하는 경우
            node = Node(elem, before.link)      # 노드 생성 + Step 1
            before.link = node                  # Step 2
```

before를 찾는 getNode(pos - 1)에 유의하라. before는 pos-1번째 노드이다. 이 연산의 시간복잡도는 어떻게 될까? 실제로 삭제하는 과정은 $O(1)$이지만 before를 찾기 위해 $O(n)$이 걸린다. 따라서 전체 시간복잡도는 $O(n)$으로 배열에서와 동일하다. 그러나 **만약 before를 알고 있다면 삽입은 $O(1)$만에 처리**된다.



### delete(pos) : 삭제 연산

삭제에서도 삭제할 pos 위치의 노드가 아니라 before 노드가 필요하다. 만약 before를 알고 있다면 삭제 연산은 다음과 같이 간단히 처리된다.

1. before의 link가 삭제할 노드의 다음 노드를 가리키도록 함 : before.link = before.link.link

![그림6 15](https://user-images.githubusercontent.com/76824867/172344481-315136bc-4c8d-4c5b-ad08-485e30844cff.PNG)

[그림 6.15] 단순연결리스트의 삭제연산


이 연산의 시간복잡도도 만약 before를 알고 있다면 한 단계만에 처리되므로 $O(1)$이다. 배열에서는 삭제할 위치를 알더라도 항목들의 이동을 위해 $O(n)$이 필요했다. 삽입에서와 같이 before를 모르고 삭제할 노드만 알고 있다면 before를 찾기 위해 $O(n)$이 필요하다. 삭제 연산 코드는 다음과 같다. insert와 마찬가지로 시작노드를 삭제하는 경우는 head가 바뀌게 되므로 특별하게 처리해주어야 한다.

``` Python
    def delete(self, pos):
        before = self.getNode(pos - 1)          # before 노드를 찾음
        if before == None:                      # 시작노드를 삭제
            if self.head is not None:           # 공백이 아니면
                self.head = self.head.link      # head를 다음으로 이동
        elif before.link != None:               # 중간에 있는 노드 삭제
            before.link = before.link.link      # Step 1
```

이 연산 역시 getNode(pos - 1)로 before를 찾기 위해 $O(n)$이 소요된다. ADT 연산들 중에서 sort와 merge는 제외한다. 정렬을 직접 구현하는 것은 약간 복잡한데 7.2절에서 간단한 정렬 알고리즘들을 다룬다. merge 연산은 크게 어렵지 않게 구현할 수 있는데, 리스트의 맨 마지막 노드의 링크가 다른 리스트의 시작 노드를 가리키도록 만들면 된다. 실습문제 P6.2에 도전해보라.

구현된 연결된 리스트 클래스를 사용하는 코드와 실행결과는 다음과 같다. 3장의 테스트 코드에서 sort와 merge 부분은 생략하였다.

``` Python
s = LinkedList()
s.display('단순연결리스트로 구현한 리스트(초기상태) :')
s.insert(0, 10);        s.insert(0, 20);    s.insert(1, 30)
s.insert(s.size(), 40); s.insert(2, 50)
s.display('단순연결리스트로 구현한 리스트(삽입x5) :')
s.replace(2, 90)
s.display('단순연결리스트로 구현한 리스트(교체x1) :')
s.delete(2);    s.delete(s.size() - 1);     s.delete(0)
s.display('단순연결리스트로 구현한 리스트(삭제x3) :')
s.clear()
s.display('단순연결리스트로 구현한 리스트(정리후) :')
```


## 6.4 원형연결리스트의 응용 : 연결된 큐

큐도 연결된 구조로 구현할 수 있는데, 이러한 큐를 **연결된 큐(Linked Queue)**라고 한다. 연결된 큐도 크기가 제한되지 않고 필요한 메모리만 사용한다는 장점과, 코드가 더 복잡하고 링크 필드 때문에 메모리 공간을 조금 더 사용하는 단점이 있다. 연결된 큐를 구현하는 가장 간단한 방법은 다음과 같이 단순연결리스트를 사용하는 것으로, 맨 앞과 뒤에 있는 노드를 **front**와 **rear**가 가리키는 구조이다. 물론 삽입은 후단(rear), 삭제는 전단(front)에서 이루어져야 한다. 이 구조의 큐 구현을 위해 프로그래밍 프로젝트 P6.3에 도전하라.

![그림6 16](https://user-images.githubusercontent.com/76824867/172344483-6f897d0b-4d46-4c5c-a727-2a81345ef5b1.PNG)

[그림 6.16] 단순연결리스트로 구현된 큐


약간 더 복잡한 구조를 생각할 수 있다. 다음과 같이 마지막 노드의 링크가 첫번째 노드를 가리키는 **원형연결리스트**를 이용하는 것이다.

![그림6 17](https://user-images.githubusercontent.com/76824867/172344487-75436d4c-44d6-479a-a42a-bce9a0f39ad6.PNG)

[그림 6.17] 원형연결리스트로 구현한 큐



이 구조에서는 tail(또는 rear)만을 변수로 저장한다. front는 어떻게 알 수 있을까? tail의 다음 노드, 즉 tail.link가 front이다.

만약 tail이 아니라 head(또는 front)만을 사용하면 어떻게 될까? 이 경우 front는 바로 접근이 가능하다. 그런데 rear도 바로 찾아갈 수 있을까? 불가능하다. 링크를 따라 후속노드 전체를 끝까지 이동해야 드디어 rear에 도착한다. 따라서 **tail을 사용하는 것이 rear와 front에 바로 접근할 수 있다는 점에서 훨씬 효율적**이다.

연결된 큐를 원형연결리스트로 구현할 때 필요한 멤버변수는 tail 뿐이다. 후단은 rear == tail이고, 삭제를 위한 전단은 front == tail.link 이므로 모두 $O(1)$만에 접근할 수 있다. 큐의 동작은 스택보다 약간 더 복잡하다.


### 클래스 정의

노드 클래스는 앞에서 공부한 스택이나 리스트에서와 동일하다. 원형연결리스트로 구현한 큐 클래스를 CircularLinkedQueue라 하자. 공백검사와 초기화, peek 등의 연산은 다음과 같이 매우 간단하다. peek는 큐가 공백이 아닐 경우 front(tail.link)의 data를 반환하면 된다.

``` Python
class CircularLinkedQueue():            
    def __init__(self):                     # 생성자 함수
        self.tail = None                    # tail : 유일한 데이터

    def isEmpty(self):                      # 공백상태 검사
        return self.tail == None

    def clear(self):                        # 큐 초기화
        self.tail = None
    
    def peek(self):                         # peek 연산
        if not self.isEmpty():              # 공백이 아니면
            return self.tail.link.data      # front의 data를 반환
```


### enqueue() : 삽입 연산

항목의 삽입은 후단을 통해 이루어진다. 삽입은 큐가 공백상태인 경우와 그렇지 않은 경우가 약간 다르다. 공백상태가 더 쉽다. 다음은 공백상태의 큐에 항목을 삽입하는 과정을 보여준다.

![A3](https://user-images.githubusercontent.com/76824867/172344432-78355ab5-323b-4b8c-a458-04e39c73a82e.PNG)

1. 입력 데이터 E를 이용해 새로운 노드 n을 생성함 : n = Node(E, None)
2. n의 링크가 자신을 가리키도록 함 : n.link = n
3. tail이 n을 가리키도록 함 : tail = n

만약 공백상태가 아니면 다음과 같이 약간 더 복잡해진다.

![A4](https://user-images.githubusercontent.com/76824867/172344434-273e97db-2bce-4901-a8b3-543e4c29b370.PNG)

1. 입력 데이터 E를 이용해 새로운 노드 n을 생성함 : n = Node(E, None)
2. n의 링크가 front를 가리키도록 함 : n.link = tail.link
3. tail의 링크가 n을 가리키도록 함 : tail.link = n
4. tail이 n을 가리키도록 함 : tail = n

``` Python
    def enqueue(self, item):                # 삽입연산
        node = Node(item, None)             # Step 1
        if self.isEmpty():                  # Case 1 : 큐가 공백상태
            node.link = node                # Case 1 : Step 2
            self.tail = node                # Case 1 : Step 3
        else:                               # Case 2 : 큐가 공백이 아님
            node.link = self.tail.link      # Case 2 : Step 2 
            self.tail.link = node           # Case 2 : Step 3
            self.tail = node                # Case 2 : Step 4
```

### dequeue() : 삭제 연산

삭제연산은 front(또는 tail.link)를 연결구조에서 꺼내고 데이터 필드를 반환하는 것이다. 큐는 반드시 공백이 아니어야 삭제가 가능하다. 큐가 항목을 하나만 가지고 있는 경우는 삭제하고나면 공백상태가 되므로 일반적인 경우와 분리해서 처리해야 한다.

![A5](https://user-images.githubusercontent.com/76824867/172344439-e333b946-a80d-4ded-9b52-4fcb6112a924.PNG)


1. n이 전단노드(front)를 가리키도록 함 : n = tail.link
2. tail이 None을 가리키도록 함 : tail = None
3. n이 가리키는 노드의 데이터를 반환함 : return n.data

큐가 2개 이상의 항목을 갖는 경우의 삭제는 다음과 같다.

![A6](https://user-images.githubusercontent.com/76824867/172344440-4657370e-3fb6-48b5-a9c4-e65de455e547.PNG)


1. n이 전단노드(front)를 가리키도록 함 : n = tail.link
2. tail의 링크가 front의 링크를 가리키도록 함 : tail.link = n.link
3. n이 가리키는 노드의 데이터를 반환함 : return n.data


``` Python
    def dequeue(self):
        if not self.isEmpty():
            data = self.tail.link.data                  # Step 1 (데이터만 저장)
            if self.tail.link = self.tail:              # Case 1 : 항목이 하나
                self.tail = None                        # Case 1 : Step 2
            else:                                       # Case 2 : 항목이 여러개
                self.tail.link = self.tail.link.link    # Case 2 : Step 2
            return data                                 # Step 3
```


### size(), print()

큐의 크기를 구하거나 큐의 내용을 출력하기 위해서는 tail부터 노드를 따라가면서 한 바퀴 돌아와야 한다. size 연산을 위한 순회 방법은 그림과 같다.

![그림6 18](https://user-images.githubusercontent.com/76824867/172344490-66d4db2a-0695-4ce9-9ac4-140c78d69c5e.PNG)

[그림 6.18] 원형연결리스트에서의 순차적인 노드의 방문

``` Python
    def size(self):
        if self.isEmpty():                  # 공백 : 0 반환
            return 0
        else:                               # 공백이 아니면
            count = 1                       # count는 최소 1
            node = self.tail.link           # node는 front부터 출발
            while not node == self.tail:    # node가 rear가 아닌 동안
                node = node.link            # 이동
                count += 1                  # count 증가
            return count                    # 최종 count 반환
```


### display()

이러한 방문 방법은 display 연산에서도 동일하게 적용된다. 코드는 다음과 같다. 루프의 종료 조건에 주의해야 한다.

``` Python
    def display(self, msg = 'CircularLinkedQueue :'):   # 디폴트 인수 사용
        print(msg, end = '')
        if not self.isEmpty():
            node = self.tail.link                       # node는 front부터 출발
            while not node == self.tail:                # node가 rear가 아닌 동안
                print(node.data, end = '')              # node 출력
                node = node.link                        # 이동
            print(node.data, end = '')                  # 마지막으로 rear 출력
        print()                                         # 한 줄 띄우기
```

테스트를 위한 코드는 5장의 원형큐와 동일한데, 큐 객체만 다음과 같이 연결된 큐(CircularLinkedQueue)를 사용하면 된다. 실행결과는 동일하다.

``` Python
q = CircularLinkedQueue()   # 연결된 큐 만들기
```

원형큐에서는 용량이 제한되었는데, 연결된 큐에서는 이런 문제가 전혀 없다. 시간복잡도는 삽입과 삭제가 모두 $O(1)$으로 원형큐와 차이가 없다.



## 6.5 이중연결리스트의 응용 : 연결된 덱

(오늘은 여기까지!! 내일부터 다시 시작!!)























## Reference

---



![그림6 19](https://user-images.githubusercontent.com/76824867/172344492-ee8130b8-8dd3-45e6-a067-d615937b7c83.PNG)
![그림6 20](https://user-images.githubusercontent.com/76824867/172344494-f9de9d53-3e35-40bb-ad1a-41073bc96829.PNG)
![그림6 21](https://user-images.githubusercontent.com/76824867/172344497-58a5071e-3bf3-463d-a5c6-68cb2b3a54c0.PNG)
![그림6 22](https://user-images.githubusercontent.com/76824867/172344500-5113fb2a-d53a-413c-980c-4c27ef140ab1.PNG)




