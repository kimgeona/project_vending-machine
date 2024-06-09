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

## Xcode 프로젝트 제거
해당 프로젝트와 관련된 모든것은 단순히 맨 처음 git clone 을 통해 다운 받았던 prject 폴더 삭제를 통해 진행하실 수 있습니다. 

## 환경 제거
설치하셨던 라이브러리와 소프트웨어들은 전부 homebrew 제거를 통해 제거하실 수 있습니다.

    # homebrew 제거하기
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/uninstall.sh)"

