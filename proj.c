#include<stdio.h>
#define ON 1
#define OFF 0
#define WITH_ENGINE_TEMP_CONTROLLER 1
#if WITH_ENGINE_TEMP_CONTROLLER
#define ENGINE_TEMP_CONTROLLER 1
#endif
void ReadEngineState(char *in, unsigned char *state);
void ReadSensorState(char *sens);
void SetTrafficLight(unsigned int *speed);
void SetRoomTemp(float *temp, unsigned char *ac);
void SetEngineTemp(float *temp, unsigned char *ctrl);
int main(void) {
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
/*************************************************************** Vehicle Variables *************************************************************/
	unsigned char EngineState = OFF;
	unsigned int VehicleSpeed = 0;
	unsigned char AC = OFF;
	float RoomTemp = 35 ;
	unsigned char EngineTempController = OFF;
	float EngineTemp = 90;
/*************************************************************** Program starts *************************************************************/
	int printnow = 0;
	char input;
	ReadEngineState(&input, &EngineState);
	if (input == 'c')
		return 0;
	char sensor = 0;
	if (input == 'a') {
		while (1) {
			ReadSensorState(&sensor);
			if (sensor == 'a') {
				char input1;
				ReadEngineState(&input1, &EngineState);
				if (input1 == 'c')
					return 0;
			}
			if (sensor == 'b') {
				SetTrafficLight(&VehicleSpeed);
				printnow = 1;
			}
			if (sensor == 'c') {
				SetRoomTemp(&RoomTemp, &AC);
				printnow = 1;
			}
			if (sensor == 'd') {
#ifdef ENGINE_TEMP_CONTROLLER
				SetEngineTemp(&EngineTemp, &EngineTempController);
				printnow = 1;
#endif
			}
			if (VehicleSpeed == 30) {
				if (AC == OFF) {
					AC = ON;
					RoomTemp = (RoomTemp * (5.0 / 4)) + 1;
				}
#ifdef ENGINE_TEMP_CONTROLLER
				if (EngineTempController == OFF) {
					EngineTempController = ON;
					EngineTemp = (EngineTemp * (5.0 / 4)) + 1;
				}
#endif
			}
/****************************************************** Display Data ********************************************************************/
			if (printnow == 1) {
				EngineState == ON ?printf("\nEngine is ON\n") : printf("Engine is OFF\n");
				AC == ON ? printf("AC is ON\n") : printf("AC is OFF\n");
				printf("Vehicle Speed = %d Km/Hr\n", VehicleSpeed);
				printf("Room Temperature = %f C\n", RoomTemp);
#ifdef ENGINE_TEMP_CONTROLLER
				EngineTempController == ON ?printf("Engine Temperature Controller is ON\n") :printf("Engine Temperature Controller is OFF\n");
				printf("Engine Temperature = %f C\n", EngineTemp);
#endif
		       printnow = 0;
			}
		}
	}
	return 0;
}
/******************************************************** Functions ******************************************************************************/
void ReadEngineState(char *in, unsigned char *state) {
	unsigned char EngineState = OFF;
	char input;
	do {
		printf("\nChoose Action to do with the Engine\n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		scanf(" %c", &input);
		if (input == 'a') {
			EngineState = ON;
			printf("Vehicle Engine is ON\n");
		}
		if (input == 'b') {
			EngineState = OFF;
			printf("Vehicle Engine is OFF\n");
		}
		if (input == 'c') {
			printf("System is Quitted\n");
		}
	} while (input == 'b');
	*in = input;
	*state = EngineState;
}
void ReadSensorState(char *sens) {
	char sensor;
	printf("\nChoose Action to do with the Sensors\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#ifdef ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	scanf(" %c", &sensor);
	*sens = sensor;
}
void SetTrafficLight(unsigned int *speed) {
	char color;
	unsigned int VehicleSpeed;
	printf("Choose the Traffic Color G or O or R\n");
	scanf(" %c", &color);
	if ((color == 'G') || (color == 'g')) {
		VehicleSpeed = 100;
	}
	if ((color == 'O') || (color == 'o')) {
		VehicleSpeed = 30;
	}
	if ((color == 'R') || (color == 'r')) {
		VehicleSpeed = 0;
	}
	*speed = VehicleSpeed;
}
void SetRoomTemp(float *temp, unsigned char *ac) {
	float RoomTemp;
	unsigned char AC;
	printf("Enter Room Temperature\n");
	scanf(" %f", &RoomTemp);
	if (RoomTemp < 10) {
		AC = ON;
		RoomTemp = 20;
	} else if (RoomTemp > 30) {
		AC = ON;
		RoomTemp = 20;
	} else {
		AC = OFF;
	}
	*temp = RoomTemp;
	*ac = AC;
}
void SetEngineTemp(float *temp, unsigned char *ctrl) {
	float EngineTemp;
	unsigned char EngineTempController;
	printf("Enter Engine Temperature\n");
	scanf(" %f", &EngineTemp);
	if (EngineTemp < 100) {
		EngineTempController = ON;
		EngineTemp = 125;
	} else if (EngineTemp > 150) {
		EngineTempController = ON;
		EngineTemp = 125;
	} else {
		EngineTempController = OFF;
	}

	*temp = EngineTemp;
	*ctrl = EngineTempController;
}

