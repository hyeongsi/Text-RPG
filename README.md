# Text RPG
<br>

## 프로젝트 소개

### 개요
지금까지 배운 C++ 내용들을 활용하여<br/>
동작하는 게임을 제작하기

## 참여 인원 - (2인)
```
* parkSihyeong46

- 플레이어, 무기, 인벤토리
```
```
* 1-blue

- 몬스터, NPC, 포탈
```
```
공통 : 스킬(파이어볼, 무적, 메테오), UI
```
<br>

## 기술 스택
* Cpp

* Visual Studio

<br>

## 시연 영상
<details>
  <summary>신규 계정 플레이</summary>
  <img width="976" src="https://user-images.githubusercontent.com/71202869/201464553-6ee3562f-9480-4f1c-bea9-ca06598f4f01.gif"/>
</details>
<details>
  <summary>기존 계정 플레이</summary>
  <img width="976" src="https://user-images.githubusercontent.com/71202869/201464754-f33684ff-4c81-4304-a857-972414be1658.gif"/>
</details>
<details>
  <summary>전투, 스킬</summary>
  <img width="976" src="https://user-images.githubusercontent.com/71202869/201464962-a4b38b0c-1480-4b79-8000-1cbf9a22aa79.gif"/>
</details>
<details>
  <summary>상점, 아이템 사용</summary>
  <img width="976" src="https://user-images.githubusercontent.com/71202869/201465152-2e911fa2-2ddb-4353-a46a-4fbdd575ce24.gif"/>
</details>
<br>

## 아쉬운점

* 게임 개발에 대해 서로 무지한 상태에서 꾸역꾸역 개발하려다 보니<br/>
이전 개발에서 헤더 문제를 해결하기 위해 사용했던 싱글톤인 GameManager에서<br/>
모든 처리를 진행하게 되어버려 코드가 커지고 구조가 복잡하게 된 부분이 많이 아쉽다.

* 개발 당시 더블버퍼링, fps에 대해 모르는 상태로 개발했기 때문에<br/>
게임이 동작함에 있어 프레임이 많이 느리다. 만들고있는 당시만 하더라도<br/>
컴퓨터가 많은 연산을 처리해서 느려지구나 라고만 생각했었기 때문에 이부분을 그대로 두고 개발하게 되었음

* 각자 개발함에 있어서 코드 스타일이 통일되지 않아<br/>
코드를 통합하거나 리뷰하는 것에 있어 서로 어려움을 느껴서<br/>
개발 중반쯤 와서야 이에 대한 심각성을 느끼고 코드구조를 통일하게 되었음

<br/>

## 기타 / 조작법
 <table>
  <tr>
    <td><b>방향키</b></td>
    <td><b>space</b></td>
    <td><b>ctrl</b></td>
    <td><b>f</b></td>
    <td><b>g</b></td>
    <td><b>h</b></td>
  </tr>
  <tr>
    <td>이동</td>
    <td>공격, 상점이용</td>
    <td>아이템 줍기</td>
    <td>공격 구체 발사</td>
    <td>공격력 버프</td>
    <td>맵 전체 광역 데미지</td>
  </tr>
</table>

```
시작일 : 2020. 10. 14.

README.md update : 2022. 11. 12.
```
