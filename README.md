AzureIOT_Arduino
==================

#### MCU : Arduino UNO WIFI R2 Board
>Connectivity : WiFi (Arduino WiFi Header : WiFiNINA )  
>Memory(Very Few) -> Flash : 48KB | SRAM : 6KB | EEPROM : 256KB   

Azure을 사용한 이유는 AWS에 사용된 예제중 BearSSL 이라는 헤더가 아두이노의 SRAM 크기보다 커서 사용이 불가능하기 때문입니다.  
해당 예제는 https://docs.microsoft.com/ko-kr/azure/iot-hub/iot-hub-mqtt-support#using-the-mqtt-protocol-directly-as-a-device 을 참고했습니다. 

##  First Step. -Make IoT Hub-
일단 Azure 계정을 만들고 IoT Hub에 들어가 새로운 IoT Hub를 만듭니다 (이미 있으시다면 그걸 사용하셔도 됩니다.)  
'크기 및 배율' 에서 F1 : 무료계층 을 이용하여도 실습용으로 충분히 이용할 수 있습니다.  
IoT Hub Name을 잘 기억해두세요.   

## Second Step. -Register IoT Device-
디바이스 ID만 입력하고 '저장'을 눌러주세요        
아두이노 ---> IoTHub 단방향 연결만 할 땐 따로 설정해야 할 정보는 없습니다.     
디바이스 ID를 잘 기억해두세요.    

## Third Step. -Make SAS Token-
MQTT 메신저를 연결하기 위해 SAS Token을 받아와야합니다.   
Azure 상단 메뉴바의 Cloud Shell ( >_ 표시 )을 실행합니다.    
처음 실행하면 어떤 구독에 CS을 설치할것인가 선택하는데, 꼭 IoT Hub를 등록한 구독에 설치해줘야 합니다.      
그다음 실행하면 화면 하단에 터미널이 나옵니다. PowerShell과 Bash중 선택해야되는데 아무거나 하셔도 상관없습니다.    
그 다음 터미널에 az extension add --name azure-cli-iot-ext 을 입력하고 설치합니다 (붙여넣기 키는 ctrl+shift+v 입니다.)      
마지막으로 터미널에 az iot hub generate-sas-token -d 디바이스 -n 허브 --du 63072000 을 입력합니다.     
디바이스와 허브는 첫번째,두번째 스텝에서 사용했던 이름으로 바꿔주세요.   
그럼 장문의 SAS 토큰 문자열이 생성됩니다. 잘 기억해두세요.   

## Last Step. -Arduino To Azure Connection-
azureIOT_Arduino.ino 파일을 다운로드받습니다.    
다음 

