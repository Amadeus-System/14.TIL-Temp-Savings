* **Date : 2022-07-17**
* **Last Modified Date : 2022-07-19**


# How to Install Kali Linux in Window 10 using WSL2

<br>
<p align="center" style="color:gray">
    <img src="https://i.pinimg.com/originals/1f/77/07/1f7707ca011ae5494189cda72002b0b4.jpg">
</p>
<center><b>Kali Linux</b></center>
<br>

<!-- TOC -->

- [How to Install Kali Linux in Window 10 using WSL2](#how-to-install-kali-linux-in-window-10-using-wsl2)
    - [WSL이란 무엇인가??](#wsl%EC%9D%B4%EB%9E%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80)
    - [VMware하고 무엇이 다른가?](#vmware%ED%95%98%EA%B3%A0-%EB%AC%B4%EC%97%87%EC%9D%B4-%EB%8B%A4%EB%A5%B8%EA%B0%80)
    - [설치 과정](#%EC%84%A4%EC%B9%98-%EA%B3%BC%EC%A0%95)
    - [준비](#%EC%A4%80%EB%B9%84)
    - [WSL2에 Kali Linux 설치하기](#wsl2%EC%97%90-kali-linux-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0)
        - [Window Mode](#window-mode)
        - [Enhanced Session Mode](#enhanced-session-mode)
        - [Seamless mode](#seamless-mode)
    - [Conclusion](#conclusion)
    - [Reference](#reference)

<!-- /TOC -->

요즘 C언어나 Fortran 또는 Linux 같은 컴퓨터 역사의 초창기 자료들에 관심이 많이 생기고 있다. 딱히 대단한 이유로 관심을 가지는 것은 아니고, 그냥 멋있어 보여서 그렇다. 힙스터 기질이 또 다시 몇년만에 고개를 들어서 최근에는 리눅스나 옛날 운영체제 등에 관심이 많다.

<br>
<p align="center" style="color:gray">
    <img src="https://i.imgur.com/awc4vPD_d.jpg?maxwidth=640&shape=thumb&fidelity=high">
</p>
<center><b>이렇게 Mr.robot Elliot 느낌으로 흑화하고 싶음..</b></center>
<br>

사실 연구용으로 Ubuntu Linux 20.04 LTS와 같은 운영체제를 사용해왔다. 그리고 이전에는 멋없는 VMWare로 가상환경에서도 해보고, 연구용 워크스테이션 서버에서 서버용 리눅스도 사용해봤는데, 뭔가 힙한 느낌이 없었다. 특히 우분투 버전의 연분홍 배경화면은 도저히 컴덕의 감성을 만족시킬 수 없는 것 같다. 

그래서 딥다크한 느낌의 프로그래밍 감성을 만족시켜줄 운영체제를 찾아보았는데.. 역시 프로그래머의 어두운 이미지하면 영화에서 흔히 보는 해커가 떠오르지 않을까? 그래서 해킹에 특화된 리눅스 버전을 찾아서 공부해보면 재미있겠구나! 하고 생각했다. 검색해보니 당연히 나처럼 생각한 사람들이 이미 그런 것을 만들어서 잘 쓰고 있었다! ㅎㅎ 보통 이런게 있겠지? 하고 검색하면 반드시 이미 존재하고 있다. 

그리고 그것이 바로 오늘 소개할 Kali Linux 라는 운영체제였던 것이다. 다만, Windows를 메인으로 쓰고 있는 상황에서 다른 운영체제를 설치하는 것은 항상 귀찮고 부담스러운 일이었다. 일단 VMware같은 가상환경은 멋도 없고, 특히 컴퓨터 소스를 나눠 사용하기 때문에 느려지는 경우가 많았다.

그래서 간편하게 운영체제를 설치하는 방법이 없는지 찾아보았는데, 몇년 동안 많은 발전이 있어서 이제는 윈도우에서 칼리 리눅스를 어플리케이션처럼 사용할 수 있는 수준까지 와 있었다! 그래서 이 방식으로 설치해보기로 했다.

현재 이 글을 쓰는 시점이 2022년 7월 17일 새벽 2시 50분인데 이제 겨우 Kali Linux 설치에 성공하고 있다. 매우 감동적이므로(..) 설치가 완료되는 동안 이에 대한 간단한 글을 써보려고 한다. 

<br>

## WSL이란 무엇인가??

WSL이란 **Windows Subsystem for Linux**의 약자로, 말 그대로 리눅스에서 사용되는 여러 어플리케이션을 윈도우에서 서브시스템으로 사용할 수 있게 해주는 기능이다. 

일반인을 대상으로 하는 컴퓨터, 노트북의 운영체제는 Microsoft Windows의 점유율이 압도적이지만, 컴퓨터로 먹고 사는 여러 연구원, 개발자들이 사용하는 서버나 환경의 운영체제는 Unix 계열의 Linux나 Mac 운영체제가 점유하고 있다.

Microsoft에서는 이런 면을 좋지 않게 생각한 것 같다. 시간이 지날수록 컴퓨터를 높은 수준으로 다루는 전문가와 그렇지 않은 일반 사용자들간의 괴리가 커질 것이고, 결국에는 고전적인 Unix 운영체제의 힘을 무시할 수 없을 것이라 생각한 것 같다. 상식적으로 생각하면, 일반 사용자를 위한 OS를 팔아서 먹고 사는 회사 안에서 엔지니어들이 모두 상대방 진영의 OS를 쓴다면 뭔가 이상할 것같기도 하다. 그래서 나온 것이 바로 WSL이다. 

간단히 말하자면, 이제 WSL을 이용해 윈도우의 Microsoft Store에서 앱을 다운로드 받듯이, 여러 리눅스 계열 운영체제의 정보를 다운받아 설치하여 사용할 수 있다!!

<br>

## VMware하고 무엇이 다른가?

VM(Virtual Machine)은 결국 실제 물리적인 컴퓨터를 구성하는 하드웨어(CPU, GPU, RAM, Storage 등)을 컴퓨터 안에서 가상으로 구현하여 컴퓨터 안의 컴퓨터를 만드는 개념이다. 일반적으로 가상환경을 셋팅해주는 프로그램을 먼저 설치하여 실행하고, 그 프로그램 안에서 미리 다운받은 다른 운영체제의 이미지 등을 설치하여 제2, 제3의 운영체제를 가상환경 프로그램 안에서 사용할 수 있다.

그러나 VMware를 사용하는 것은 다소 번거롭다. 일단 윈도우 화면에서 가상환경 프로그램을 실행한 뒤, 그 안에서 가상환경 안에 설치된 리눅스를 부팅해야 하기 때문이다. 사용할 때마다 일일이 운영체제를 부팅해야 한다는 것도 귀찮은 일이다. 

또한 내 노트북의 성능 문제인지는 모르겠지만, 리눅스 우분투를 VMware에서 설치하여 사용하면 일정기간 이후 굉장히 렉이 걸려서, 도저히 사용못할 수준이 되는 현상이 자주 발생했다. 그래서 연구용으로 사용하는 리눅스 서버를 제외하면, 내가 노트북에 설치한 리눅스는 한달도 지나지 않아, 가상환경 프로그램과 함께 통째로 삭제되는 일이 반복되었다. 몇 년에 한번씩 리눅스 힙스터 기질이 생겨서 설치하고, 한달 후 휴지통에 버리는 일이 반복되었다.

<br>

## 설치 과정

이제 본격적으로 Kali Linux를 WSL을 이용하여 설치해보자! 단순히 서버버전 리눅스만 설치할 수도 있지만, 멋진 배경화면을 갖는 칼리 리눅스를 보기 위해 GUI 환경까지 지원해주는 Win-Kex까지 함께 설치해서 윈도우와 유사한 사용자 경험을 해보자. 여기서 **Win-Kex**는 WSL2용 칼리 리눅스에 대한 데스크탑 경험을 제공하는 서비스이다. 대략 다음과 같은 것들이 가능하다고 한다.

* 창 모드로 전용 창에서 Kali Linux 데스크탑 시작하기
* Windows와 Kali 어플리케이션 및 메뉴 간에 Windows 바탕화면 공유하기
* 사운드 지원
* 비권한 및 루트 세션 지원
* Kali Linux와 Windows 어플리케이션 사이의 복사 및 붙여넣기 등을 지원하는 공유 클립보드 지원
* 다중 세션 지원 : 루트 창 및 비공개 창 및 Seamless 세션을 동시에 가능
* WSLg와 완벽하게 호환

<br>

## 준비

설치하려면 다음 두 조건이 필요하다

* Windows 10 버전
* Windows PowerShell 사용

<br>

## WSL2에 Kali Linux 설치하기

1. 우선 Windows Powershell을 관리자 권한으로 열고 다음 명령어를 실행한다.

``` Shell
Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
```

2. 컴퓨터를 재시작(Restart) 한다.

3. 다시 Windows PowerShell을 관리자 권한으로 열고 다음 명령어를 실행한다. 두 개의 명령어이므로 한 줄씩 차분하게 실행하자.

``` Shell
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

4. 다시 재시작한다.

5. [여기](https://docs.microsoft.com/en-us/windows/wsl/install-manual#step-4---download-the-linux-kernel-update-package)에 가면 **WSL2 Linux kernel update package for x64 machines**라는 링크가 있을텐데, 이것을 클릭하면 **wsl_update_x64.msi** 파일이 자동으로 다운로드된다. 다운이 완료되면 다운로드 폴더에 가서 msi 파일을 더블클릭하고 설치하자! 그냥 next만 누르면 된다.

6. 다시 PowerShell을 관리자 권한으로 열고 다음 명령어를 실행하자. WSL을 버전 2로 설정하는 명령어이다.

``` Shell
wsl --set-default-version 2
```

7. 이제 윈도우 메뉴에서 Microsoft Store를 검색해서, 어플리케이션 다운받는 곳에 들어간다. 'Kali Linux'를 검색하여, 어플을 다운로드 받자.

8. 다운로드가 다 되면 Store에서 직접 실행하거나, 윈도우 메뉴창에서 kali Linux를 검색하면 아이콘이 뜬다. 그것을 실행하자.

**주의!!** Kali linux를 처음 실행하면 검은 화면의 터미널 창이 뜨면서 초기 설치를 위해 기다리라는 메시지가 나온다.

``` Shell
installing.. a few minutes may take..
``` 

정상 설치되면 문제없지만, 상황에 따라 이런 에러가 발생할 경우가 있다.

``` Shell
Error 0x80370102... 
```

이 메시지는 WSL2로 Kali Linux를 실행하기 위해 하드웨어에서 가상환경을 지원해주어야 하는데, 그것에 대한 옵션이 막혀있다는 뜻이다. 따라서 막혀있는 옵션을 풀어주어야 한다.

**제어판** $\rightarrow$ **프로그램** $\rightarrow$ **프로그램 및 기능** $\rightarrow$ **Windows 기능 켜기/끄기**로 들어가자.

<br>
<p align="center" style="color:gray">
    <img src="https://media.vlpt.us/images/jaylnne/post/c4fae4fa-ac88-4eaa-b797-da0151ff1136/image.png">
</p>
<center><b></b></center>
<br>

다음과 같은 창이 뜰텐데 여기서 다음 3가지 옵션을 모두 선택하자.

1. **Linux용 Windows 하위 시스템 기능 켜기** 옵션을 체크 --> 시스템 재시작
2. **가상머신 플랫폼 기능** 옵션을 체크 --> 시스템 재시작
3. **Hyper-V 기능** 옵션을 (하위 카테고리까지 모두) 체크 --> 시스템 재시작

이 3가지 옵션이 모두 해제되어 있지는 않고, 한 두가지만 체크가 안되어있을 것이다. 체크가 안 되어 있는 옵션만 체크하고 재시작하자. 재시작하면 이제 변경된 옵션이 적용된 상태이다. 여기서 마지막으로 한번 더 귀찮은 짓을 하면 끝이다.

4. BIOS 설정에 들어가서 가상환경 설정 활성화 켜주기

컴퓨터 재시작 --> Windows 실행 전 검은 화면에서 del키 또는 F2키를 팍팍 눌러주자 --> BIOS라는 컴퓨터 또는 노트북의 하드웨어 정보를 보여주는 환경으로 진입한다 --> Advanced --> CPU configuration --> Intel (VMX) Virtualization Technology (또는 Armed 디바이스의 경우, SVM 옵션)이 disabled로 사용불가능하게 되어있으면, 사용가능하게 옵션을 바꿔주자!

<br>
<p align="center" style="color:gray">
    <img src="https://media.vlpt.us/images/jaylnne/post/b408412d-65ba-4831-8b59-d54af97f87d2/image.png">
</p>
<center><b>BIOS 진입 화면</b></center>
<br>

Intel이면 VMX이고, Arm 디바이스면 SVM이라고 되어있을 것이다. Disabled에서 Enabled로 바꿔주자. 이제 하드웨어가 가상환경을 지원하도록 작동한다는 뜻이다. 참고로 내 컴퓨터는 ASUS 기준이어서 다른 PC 모델은 조금씩 다를 수 있는데, 잘 찾아보자. 

여기까지 다 했으면 이제 다시 메뉴에서 Kali linux를 검색하여 실행하자! 이제 정상적으로 초기 설치가 될 것이다. 칼리 리눅스 운영체제의 최상위 유저를 지정하는 ID와 Password를 자기 마음대로 입력해주면, 설치가 진행된다.

그리고 중간에 다음과 같이 키보드 레이아웃을 선택하라는 창이 뜰 것이다.

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741070-5afc413b-b481-4287-ba14-712a9e0fe02f.PNG">
</p>
<center><b>키보드 레이아웃 설정</b></center>
<br>

영어 키보드 레이아웃밖에 없을텐데, 여기서 others를 선택하고 ok로 넘어가자. 국적은 korean으로 선택!

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741078-f5e170ec-a8c7-4a49-bf97-e8222b2614f6.PNG">
</p>
<center><b>국적 설정</b></center>
<br>

그 다음에 한국어 키보드 레이아웃 중에서 나는 101-104 호환 옵션을 선택했다. 현재까지 아무 문제없이 사용되는듯.

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741081-782ee295-dc5a-49ca-9e05-e217cfa4c095.PNG">
</p>
<center><b>키보드 레이아웃 설정</b></center>
<br>

키보드 레이아웃까지 설정완료되면, 이제 남은 초기설치가 진행된다. 여기서 5~10분 정도 걸리니 느긋하게 커피 한잔 끓여오자.

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741084-3e1c20bb-4e80-4687-855c-bb076ef87638.PNG">
</p>
<center><b>설치과정. 5~10분 정도 걸린다.</b></center>
<br>

설치가 다 되었으면, 이제 **Win-Kex**를 설치해야 한다. 이게 없어도 칼리 리눅스를 사용할 수 있지만, 서버 버전이므로 초심자는 조금 답답할 것이다. GUI 환경까지 설치해보자!

다음 명령어를 차분하게 실행한다.

``` Shell
kali@kali:~$ sudo apt update
kali@kali:~$
kali@kali:~$ sudo apt install -y kali-win-kex
```

여기서 **sudo**는 **superuser do** 라는 의미로, 유닉스 계열 운영체제에서 최상위권한의 사용자로 명령을 실행한다는 뜻이다. 처음에 입력했었던 ID와 password를 기억하고 있어야 한다.

다 설치하고 나면 이제 다음 커맨드로 실행하자. -s는 사운드 지원을 해준다는 옵션이다.

``` Shell
kex --win -s
```

이제 다음과 같은 칼리 리눅스 운영체제를 볼 수 있다.

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741086-1995b946-0a26-4a83-9436-70c397e9fc08.PNG">
</p>
<center><b>Kali Linux Initial Screen with Warning</b></center>
<br>

참고로 나는 프로그램 하나가 설치가 안되어서, 경고창이 뜨는데 remove해도 사용에 딱히 문제가 없었다. 어차피 설치 이상하게 되면 다 삭제하고 처음부터 하거나 수정가능할 것이므로 그냥 넘어가자.

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741088-96f43a0f-50dc-449a-8592-6a76f4af929d.PNG">
</p>
<center><b>Kali Linux Initial Screen</b></center>
<br>

<br>
<p align="center" style="color:gray">
    <img src="https://user-images.githubusercontent.com/76824867/179741090-b0748e5e-d379-4df8-a06f-7209fb370ebf.PNG">
</p>
<center><b>Kali Linux Terminal</b></center>
<br>

터미널에서 리눅스 명령어도 문제없이 작동한다. 위의 메뉴에서 Firefox 브라우저로 인터넷에서 유튜브로 들어가서 잘 되는지까지 테스트해보았다. 문제없이 잘 된다.

그런데 칼리 리눅스에서는 언어를 korean으로 하면 **한글 폰트가 깨지는 현상**이 발생한다. 이를 해결하는 방법은 다음과 같다. 다음 5가지 명령어를 하나씩 차례대로 실행하자. 비밀번호를 기억하고 있어야 한다.

``` Shell
sudo apt -y update
sudo apt -y upgrade
sudo apt-get install fcitx-hangul
sudo apt-get install fcitx-lib*
sudo apt-get install fonts-nanum*
```

5개의 명령을 모두 완료했으면, 칼리 리눅스를 모두 종료하고 다시 실행하자. 이제 인터넷창을 켜보면 한국어 폰트가 깨지지 않고 제대로 보인다는 것을 알 수 있을 것이다. 참고로 Kali linux 홈페이지 설명에 따르면, 다음과 같은 3가지 GUI를 사용할 수 있는 것 같다.

<br>

### Window Mode

이 모드는 아마도 가장 일반적인 Kali Linux의 GUI 바탕화면 같다. 연분홍 바탕화면의 Ubuntu와는 차원이 다른 힙함이 느껴진다(..)

<br>
<p align="center" style="color:gray">
    <img src="https://www.kali.org/docs/wsl/win-kex/win-kex.png">
</p>
<center><b>Kali Linux Window Mode</b></center>
<br>

Window Mode를 Sound Support와 함께 열고 싶다면 다음 명령어를 실행하면 된다.

``` shell
kex --win -s
```

<br>

### Enhanced Session Mode

이 모드는 아마도 Kali Linux의 여러 보안/해킹 관련 기능을 적극적으로 쓸 수 있게 도와주는 모드 같다.

<br>
<p align="center" style="color:gray">
    <img src="https://www.kali.org/docs/wsl/win-kex/win-kex-2.png">
</p>
<center><b>Kali Linux Enhanced Session Mode (ESM)</b></center>
<br>

이 모드에서 Sound Support와 Arm Workaround 옵션을 함께 실행하려면 다음과 같이 하면 된다.

``` shell
kex --esm --ip -s
```

<br>

### Seamless mode
    
이 모드는 일반적인 윈도우 바탕화면에서 칼리 리눅스의 여러 프로그램을 마치 윈도우 프로그램 실행하듯이 사용할 수 있는 모드이다. 리눅스 어플리케이션과 윈도우 사용자환경의 결합이라고 할 수 있는 부분이며, 아마 WSL 홍보에서도 이러한 측면을 강조했던 것 같다. 간단히 칼리 리눅스 프로그램을 사용한다면 이 모드도 괜찮은 것 같다.

<br>
<p align="center" style="color:gray">
    <img src="https://www.kali.org/docs/wsl/win-kex/win-kex-sl.png">
</p>
<center><b>Kali Linux Seamless Mode</b></center>
<br>

sound support와 함께 이 모드를 사용하려면 다음 명령어를 사용하면 된다.

``` shell
kex --sl -s
```

이 모드들에 대한 자세한 설명은 [Win-KeX SL usage documentation](https://www.kali.org/docs/wsl/win-kex-sl/)에 자세히 나와있다.

<br>

## Conclusion

이렇게 Kali Linux 설치를 완료하였다. 리눅스 운영체제를 윈도우즈 기반의 환경에 설치하는 것은 언제나 쉽지 않다. 분명 인터넷에서 알려주는대로 똑같이 해도 내 컴퓨터에서만 발생하는 에러(..)가 있었기 때문에, 온전하게 설치하는 것이 생각보다 조금 힘들었다. 앞으로 시간날때 Kali Linux Tutorial을 따라해봐야겠다.

<br>

## Reference

* 칼리 리눅스 설치과정 : https://www.kali.org/docs/wsl/win-kex/
* 하드웨어 변경 : https://askubuntu.com/questions/1264102/wsl-2-wont-run-ubuntu-error-0x80370102
* 한글 폰트 : https://programforlife.tistory.com/42
