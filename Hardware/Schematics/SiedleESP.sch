EESchema Schematic File Version 4
LIBS:SiedleESP-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP8266:ESP-01v090 IC1
U 1 1 5C30DF1D
P 5850 3050
F 0 "IC1" H 5850 3565 50  0000 C CNN
F 1 "ESP-01v090" H 5850 3474 50  0000 C CNN
F 2 "" H 5850 3050 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 5850 3050 50  0001 C CNN
	1    5850 3050
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 5C3142F3
P 2900 2700
F 0 "D1" H 2900 2484 50  0000 C CNN
F 1 "1N4007" H 2900 2575 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2900 2525 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2900 2700 50  0001 C CNN
	1    2900 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3100 4800 3100
Wire Wire Line
	4800 3100 4800 3200
Connection ~ 4800 3200
Wire Wire Line
	4800 3200 4900 3200
Wire Wire Line
	4900 3000 4800 3000
Wire Wire Line
	4800 3000 4800 3100
Connection ~ 4800 3100
$Comp
L Device:C C1
U 1 1 5C315277
P 8150 3300
F 0 "C1" H 8265 3346 50  0000 L CNN
F 1 "10n" H 8265 3255 50  0000 L CNN
F 2 "" H 8188 3150 50  0001 C CNN
F 3 "~" H 8150 3300 50  0001 C CNN
	1    8150 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5C31531B
P 7250 3300
F 0 "C2" H 7365 3346 50  0000 L CNN
F 1 "100µ" H 7365 3255 50  0000 L CNN
F 2 "" H 7288 3150 50  0001 C CNN
F 3 "~" H 7250 3300 50  0001 C CNN
	1    7250 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3450 7700 3750
Connection ~ 7700 3750
Wire Wire Line
	7700 3750 7750 3750
$Comp
L LD1117V33:PMIC-LD1117V33(TO-220) U1
U 1 1 5C3146C2
P 7700 3750
F 0 "U1" H 7700 3972 50  0000 C CNN
F 1 "LD1117V33" H 7700 4063 50  0000 C CNN
F 2 "TO-220" H 7700 3750 50  0001 L BNN
F 3 "STMicroelectronics" H 7700 3750 50  0001 L BNN
F 4 "Unavailable" H 7700 3750 50  0001 L BNN "Feld4"
F 5 "LD1117 Series 3.3 V 800 mA Low Drop Fixed Positive Voltage Regulator - TO-220" H 7700 3750 50  0001 L BNN "Feld5"
F 6 "None" H 7700 3750 50  0001 L BNN "Feld6"
F 7 "TO-220 STMicroelectronics" H 7700 3750 50  0001 L BNN "Feld7"
F 8 "LD1117V33" H 7700 3750 50  0001 L BNN "Feld8"
	1    7700 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 5C315ED0
P 3250 2850
F 0 "C3" H 3365 2896 50  0000 L CNN
F 1 "10µ" H 3365 2805 50  0000 L CNN
F 2 "" H 3288 2700 50  0001 C CNN
F 3 "~" H 3250 2850 50  0001 C CNN
	1    3250 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5C315F41
P 3700 2700
F 0 "R1" V 3493 2700 50  0000 C CNN
F 1 "2k2" V 3584 2700 50  0000 C CNN
F 2 "" V 3630 2700 50  0001 C CNN
F 3 "~" H 3700 2700 50  0001 C CNN
	1    3700 2700
	0    1    1    0   
$EndComp
$Comp
L Isolator:PC817 U?
U 1 1 5C315FF5
P 4350 2800
F 0 "U?" H 4350 2483 50  0000 C CNN
F 1 "PC817" H 4350 2574 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 4150 2600 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 4350 2800 50  0001 L CNN
	1    4350 2800
	1    0    0    1   
$EndComp
Text Label 2550 2700 2    50   ~ 0
HTA-711-0_PIN-7
Text Label 2550 3000 2    50   ~ 0
HTA-711-0_PIN-c
Text Label 8600 2900 0    50   ~ 0
USB-GND
Text Label 8600 3750 0    50   ~ 0
USB-5V
Wire Wire Line
	7250 3750 7700 3750
Wire Wire Line
	8150 3150 8150 2900
Wire Wire Line
	6800 2900 7250 2900
Connection ~ 8150 2900
Wire Wire Line
	8150 2900 8600 2900
Wire Wire Line
	7250 3150 7250 2900
Connection ~ 7250 2900
Wire Wire Line
	7250 2900 8150 2900
Wire Wire Line
	7250 3450 7250 3750
Connection ~ 7250 3750
Wire Wire Line
	8150 3450 8150 3750
Wire Wire Line
	8600 3750 8150 3750
Connection ~ 8150 3750
Wire Wire Line
	7250 3750 4700 3750
Wire Wire Line
	4700 3750 4700 3200
Wire Wire Line
	4700 3200 4800 3200
Wire Wire Line
	2550 2700 2750 2700
Wire Wire Line
	3050 2700 3250 2700
Connection ~ 3250 2700
Wire Wire Line
	3250 2700 3550 2700
Wire Wire Line
	3850 2700 4050 2700
Wire Wire Line
	4650 2900 4900 2900
Wire Wire Line
	4050 2900 4000 2900
Wire Wire Line
	4000 2900 4000 3000
Wire Wire Line
	4000 3000 3250 3000
Connection ~ 3250 3000
Wire Wire Line
	3250 3000 2550 3000
Wire Wire Line
	4650 2700 4800 2700
Wire Wire Line
	4800 2700 4800 2400
Wire Wire Line
	4800 2400 7250 2400
Wire Wire Line
	7250 2400 7250 2900
$EndSCHEMATC
