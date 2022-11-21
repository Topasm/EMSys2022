// 모듈형 문자 디바이스 드라이버(hello_drv.c) 및
// 응용프로그램 설계, 실행 순서 요약
//  PC에서
//  디바이스 드라이버 “hello_drv.c” 작성


//  Makefile 작성
//  Compile(make명령) 후, Target으로 ‘hello_drv.ko’ 를 전송 (scp, minicom, whatever)
//  키트에서
//  디바이스 노드 생성 (mknod)
//  디바이스 드라이브 적재 (insmod)
//  PC에서
//  응용프로그램 작성 (hello_test.c)
//  응용프로그램 컴파일 후, 실행 파일 (hello_test)을 타겟으로 전송
//  응용 프로그램 실행 (./hello_test