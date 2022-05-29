/*
    Identification Authentication Management
    이하 IAM은 사용자의 식별과 인증을 관리하는 라이브러리입니다.
*/
#ifndef __PID_H__
#define __PID_H__

/*          User Management         */
void            addUser();      // 로그인 정보가 존재하지 않을 경우 데이터셋 생성
void            delUser();      // 사용자 탈퇴 OR 사용자 자격 박탈
void            prtUser();      // 사용자 정보 출력 (대출 권수, 대출 목록)

/*          Indentification & Authentication        */
void            logUser();      // 사용자 로그인 기능 함수
unsigned int    getUser();      // 사용자 정보 가져오기

#endif  // _PID_H__

