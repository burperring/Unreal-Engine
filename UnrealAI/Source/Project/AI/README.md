# Unreal_AI_System

Unreal AI System과 Behavior Tree를 이용한 NPC 구현

- 제작 기간 : 2025년 12월 1일 ~ 2026년 2월 28일

## 🖥️ 개요
### 목적
1) Unreal AI System과 Behavior Tree 구현을 통한 NPC AI 시스템 이해
2) Pawn 기반, Character 기반 AI 구현을 통한 시스템 이해

## 🎮 주요 구현
### PD_AIController_Base:
  - UAISenseConfig_Sight, UAISenseConfig_Hearing, UAISenseConfig_Damage를 이용한 시야, 소리, 데미지 센서 감지 구현
  - PerceptionUpdated와 TargetPerceptionUpdated를 통한 감지 동작 구현
  - CanSenseActor를 통한 감지 기능 동작 확인 구현
### BTTask:
  - PD_BTTask_PatrolRandomLocation : 랜덤 패트롤 이동 구현
  - PD_BTTask_ClearBBKeyValue : BB Key값 제거 구현
  - PD_BTTask_GhostMove : Pawn 기반 AI의 Move to 구현
### BTService:
  - PD_BTService_ChangeSpeed : AI 이동 속도 변경 구현
  - PD_BTService_PlayerInAttackRange : AI 공격 가능 여부 검사 구현
### PD_NPCFloatingPawnMovement:
  - RotateToMovementDirection : Pawn AI 회전 함수 구현
  - ApplyGravity : Pawn AI 중력 함수 구현
  - IsConsideredGrounded와 CheckGround 함수를 통한 바닥 검사 구현

<img width="880" height="418" alt="Image" src="https://github.com/user-attachments/assets/b229a195-c86a-49cd-840e-6a10cd171d71" />

### Character 기반 AI 움직임 구현
[![Video Label](http://img.youtube.com/vi/X-sqqreaP1Y/0.jpg)](https://www.youtube.com/watch?v=X-sqqreaP1Y)

### Pawn 기반 AI 움직임 구현(귀신 AI - NavMesh Move To와 다른 방식의 움직임)
[![Video Label](http://img.youtube.com/vi/2CcAArDH73s/0.jpg)](https://www.youtube.com/watch?v=2CcAArDH73s)
