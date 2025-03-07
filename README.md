# 2Platoon
![image](https://github.com/user-attachments/assets/88010164-ac4c-4aa5-9fb1-a087625a2cd9)
닌텐도의 '스플래툰'을 참고하여 TPS 슈팅 게임을 구현했다.
## 🖥️ 개요
플레이어가 총을 발사해 레벨에 배치된 풍선을 모두 터트리면 포탈이 활성화 되고, 이 포탈을 통해 다음 레벨로 진입할 수 있다. 마지막 레벨에서는 트로피가 활성화 되고, 트로피를 획득하면 클리어되며 플레이어의 최종 점수가 출력된다.

(1) 풍선을 터트리면 나오는 진주알을 습득하거나, (2) 몬스터를 타격하면 플레이어의 점수가 올라간다.
### 1. 팀원
- 김동현
- 김성진
- 김도훈
- 윤하은
- 최지한
### 2. 기간
- 2025.02.17 ~ 2025.03.07
### 3. 기술 스택
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![Rider](https://img.shields.io/badge/Rider-000000.svg?style=for-the-badge&logo=Rider&logoColor=white&color=black&labelColor=crimson)
![Unreal Engine](https://img.shields.io/badge/unrealengine-%23313131.svg?style=for-the-badge&logo=unrealengine&logoColor=white)
![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)
![Blender](https://img.shields.io/badge/blender-%23F5792A.svg?style=for-the-badge&logo=blender&logoColor=white)

## 🎮 주요 구현
### 1. 조작키
- **이동**: WASD
- **점프**: SpaceBar
- **발사**: LMB
- **플레이어 변신**: C
### 2. 페인트 총
- 마우스 좌클릭으로 총을 발사해 탄환이 부딪히면 페인트 데칼을 생성한다.
![Image](https://github.com/user-attachments/assets/a8dd2820-93c5-4064-b41b-b26e8bb95a7e)
### 3. 플레이어 변신
- C를 눌러 오징어로 변신하면, 일반 필드에서는 기본 속도보다 느려지고 페인트 위에서는 기본 속도보다 빨라진다. 발사는 비활성화 된다.
![Image](https://github.com/user-attachments/assets/cb612631-30e3-4370-9087-3fb7b8cada20)
- 오징어 상태에서 페인트 위로 진입 시 탄환이 서서히 장전된다.
![Image](https://github.com/user-attachments/assets/baae8f5e-684d-4365-8f48-9ac886c04440)
### 4. 몬스터 (AI)
- 근거리 몬스터
![Image](https://github.com/user-attachments/assets/cfcc3e53-2282-472c-a8ac-4e1351fdd36b)
- 원거리 몬스터
![Image](https://github.com/user-attachments/assets/c754cb3b-d096-48d8-9abf-4986be7ac339)
### 5. 레벨 이동
- 필드에 배치된 풍선을 모두 터트리면 포탈이 활성화 된다.
![Image](https://github.com/user-attachments/assets/8e151156-5c53-4ec0-bd01-08db69f6a89e)
![Image](https://github.com/user-attachments/assets/0ec9d7e2-b8e1-4fb9-aabd-ec2e8c328d80)
- 마지막 레벨에서 풍선을 모두 터트리면 트로피가 나타난다.
- 트로피를 획득하면 게임을 클리어하게 된다.
