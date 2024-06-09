# Vending-Machine (v.1.0.0)

"Vending-Machine"은 C++ 언어로 작성된 GUI 자판기 어플리케이션입니다. 어플리케이션은 서버와 클라이언트 총 2개가 제공되며 TCP/IP 소켓 프로그래밍을 통해 서로 관리되고 제어됩니다.

현재 해당 프로그램은 실행파일이 아닌 원본 소스코드로 제공됩니다. 사용하시기 위해서는 IDE 프로젝트를 생성하시고 이를 통해 각 프로그램을 빌드하셔서 사용하셔야 합니다. (방법은 다음 절에서 설명합니다.)

>지원 환경 : MacOS(Xcode)

## 업데이트 내용 (v.1.0.0)
* 자판기 프로그램 첫 배포.

## 환경 준비
프로젝트를 생성하기 위해서는 응용프로그램 git, make, cmake, homebrew와 자판기에서 사용할 C++ 라이브러리인 gtkmm4가 필요합니다. 해당 프로그램들을 먼저 설치하시고 다음 과정을 따라 주시기 바랍니다. 

다음은 homebrew를 설치하고 이를 이용해 git, make, cmake를 install 하는 방법입니다.

    # homebrew 설치하기
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    # git 설치하기
    $ brew install git

    # make 설치하기
    $ brew install make

    # cmake 설치하기
    $ brew install cmake

    # gtkmm4 설치하기 
    $ brew install gtkmm4


## Xcode 프로젝트 생성
프로젝트 관리 도구(Project)를 이용하여 자판기 프로젝트를 다운받고 빌드합니다. 방법은 다음과 같습니다.

    # 프로젝트 관리 도구(Project) 다운
    $ git clone https://github.com/kimgeona/project.git

    # 프로젝트 관리 디렉토리로 이동
    $ cd prject

    # 프로젝트 관리 디렉토리에서 자판기 프로젝트 다운받고 빌드
    $ make project PROJECT_REPO=https://github.com/kimgeona/project_vending-machine.git

프로젝트 관리 도구(Project)에 대한 자세한 설명은 다음 링크에서 소개되어 있습니다. 혹시 해당 과정에서 문제가 발생한다면 링크를 참조하세요. https://github.com/kimgeona/project.git

## Xcode 프로젝트 열기
위 과정을 마치면 Xcode 프로젝트는 project/project_vending-machine/build에서 확인하실 수 있습니다. (클릭해서 프로젝트를 실행하시면 됩니다.)

## 프로그램 사용 방법
프로젝트를 빌드하면 총 2개의 실행파일 client와 server가 Xcode 프로젝트 폴더 내에 생성됩니다. 해당 실행파일을 실행하고자 하는 디렉토리로 가져오시거나 복사하셔서 실행하시면 됩니다.

> 1. client와 server 응용프로그램은 독립적으로 작동하므로 순서 상관없이 실행하셔서 사용해도 무방합니다.
> 2. 하나의 프로그램만 실행하셔서 사용하셔도 됩니다.
> 3. client 프로그램은 강제종료되면 기존 자판기의 상태가 "on"인 상태로 종료가 되어 파일이 열리지 않을 수 있습니다. 꼭 정상 종료(윈도우 x 버튼) 해주시기 바랍니다.
> 4. 만약 client 프로그램이 강제종료가 되어버리는 바람에 자판기가 계속해서 실행중으로 뜨고 열리지 않는다면 "자판기이름_data.txt" 파일 내부에 state="on"을 state="off"로 바꿔주시면 해결됩니다.


## Xcode 프로젝트 제거
해당 프로젝트와 관련된 모든것은 단순히 맨 처음 git clone 을 통해 다운 받았던 prject 폴더 삭제를 통해 진행하실 수 있습니다. 

## 환경 제거
설치하셨던 라이브러리와 소프트웨어들은 전부 homebrew 제거를 통해 제거하실 수 있습니다.

    # homebrew 제거하기
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/uninstall.sh)"

