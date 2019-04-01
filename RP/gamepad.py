import pygame
import thread
import time
import socket
import os

#----------------------------------------------CONSTANTES---------------------------------------------#
HOST = '192.168.0.100'
PORT = 5000

PUSH_L_BUTTON	= 10
PUSH_R_BUTTON	= 11
D_L2         	= 6
D_R2         	= 7
D_L1            = 4
D_R1            = 5
TRIANGLE_BUTTON = 3
CIRCLE_BUTTON   = 1
X_BUTTON        = 0	
SQUARE_BUTTON   = 2
SELECT		= 8 
START		= 9

A_UPDOWN_ARROW   = 4 
D_LEFTRIGHT_ARROW= 5
A_LEFTRIGHT_L    = 0
A_UPDOWN_L       = 1
A_LEFTRIGHT_R    = 2
A_UPDOWN_R       = 3
A_L2             = 4
A_R2             = 5

DELAY = 0.001

#------------------------------------BUSQUEDA DE MANDOS RECONOCIDOS-----------------------------------#
def getJoystick():
        NAME = ["4Axis 12Button USB Vibration Gamepad", "4-Axis,12-Button with POV","USB, 3-axis, 4-button joystick", "Logitech Extreme 3D Pro USB", "DragonRise Inc.   Generic   USB  Joystick  ", "MY-POWER CO.,LTD. 2In1 USB Joystick", "Sony PLAYSTATION(R)3 Controller", "PLAYSTATION(R)3 Controller", "PS(R)Gamepad", "Controller (XBOX 360 For Windows)", "Gamepad"]
        pygame.init()
        

        pygame.joystick.init()
        joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]

        joy = pygame.joystick
        idx = 0
        found = False

        while not found:
                print "Buscando joystick compatible..."
                for item in range(joy.get_count()):
                        if joy.Joystick(item).get_name() in NAME:
                                idx = joy.Joystick(item).get_id()
                                found = True
                                break
                time.sleep(1)
        gamePad = joy.Joystick(idx)
        return gamePad

#------------------------------------SOLICITAR POSICIONES AL MANDO------------------------------------#
def getPositions(gPad):
        pygame.event.pump()
        axes = []
        buttons = []
        
        for i in range(gPad.get_numaxes()):
                axes.append(int(gPad.get_axis(i)*100))
        for i in range(gPad.get_numbuttons()):
                buttons.append(gPad.get_button(i))
        
        axes = axes[0:4] + axes[6:8]
        buttons = buttons[0:2] + buttons[3:5] + buttons[6:12] + buttons[13:15]
	#print buttons[0:2] + buttons[3:5] + buttons[6:12] + buttons[13:15]
	#print axes[0:4] + axes[6:8]
	
        os.system('clear')
        return axes, buttons

#-----------------------------------------------CLIENTE-----------------------------------------------#
def startClient():
        socketClient = socket.socket()
        socketClient.connect((HOST, PORT))
        socketClient.send(InstructionChain)
        time.sleep(DELAY)

#-----------------------------------------------ENCODER-----------------------------------------------#
def EncodeInstruction(Instruction):
        alphabet = "0ABCDEFGHIJjihgfedcba"
        index = int(round(Instruction/10.0))
        
        return alphabet[index]
        
#---------------------------------------SOLICITAR INSTRUCCIONES---------------------------------------#
def getInstructions(axes, buttons, Light, Magnet, Vel):
        OutputInstructions = []
        LState=0
        MState = 0

        ##################################################################
        #####################   ACELERAR/RETROCEDER   ####################
        ##################################################################
        Acelerar1 = buttons[D_R2]*100
        Acelerar2 = buttons[D_L2]*-100
        Acelerar = Acelerar1 + Acelerar2
        OutputInstructions.append(EncodeInstruction(Acelerar))
        
        ##################################################################
        #####################      ACELERAR GIRO      ####################
        ##################################################################
        direccion = axes[A_LEFTRIGHT_L]
        if direccion > 40:
                direccion = 99
        elif direccion < -40:
                direccion = -99

        OutputInstructions.append(EncodeInstruction(direccion))
        ##################################################################
        #####################         CAMARA          ####################
        ##################################################################
        CamaraRL = axes[A_UPDOWN_R]
        CamaraUD = axes[A_LEFTRIGHT_R]*-1
        if CamaraRL > 40:
                CamaraRL = 99
        elif CamaraRL < -40:
                CamaraRL = -99

        if CamaraUD > 40:
                CamaraUD = 99
        elif CamaraUD < -40:
                CamaraUD = -99


        OutputInstructions.append(EncodeInstruction(CamaraRL))
        OutputInstructions.append(EncodeInstruction(CamaraUD))

        ##################################################################
        #####################         SERVOS          ####################
        ##################################################################
        Servo1 = axes[A_UPDOWN_ARROW]
        Servo2 = axes[D_LEFTRIGHT_ARROW]*-0.25
        Servo = Servo1 - Servo2

        OutputInstructions.append(EncodeInstruction(Servo))
        #OutputInstructions.append(EncodeInstruction(Servo1))
        #OutputInstructions.append(EncodeInstruction(Servo2))

        ##################################################################
        #####################   Garra Abrir y cerrar  ####################
        ##################################################################
        HandOpen  = buttons[SQUARE_BUTTON]*100
        HandClose = buttons[CIRCLE_BUTTON]*-100
        HState = HandOpen + HandClose
        
        
        OutputInstructions.append(EncodeInstruction(HState))

        ##################################################################
        ##################           Home camara        ##################
        ##################################################################
        HCamera  = buttons[START]*100
        
        
        OutputInstructions.append(EncodeInstruction(HCamera))
        ##################################################################
        ################## Electroiman encender y apagar #################
        ##################################################################
        CaseOpen  = buttons[D_R1]*100
        CaseClose = buttons[D_L1]*100
                
        if CaseOpen == 0 and CaseClose == 100:
                MState = 100
        elif CaseOpen == 100 and CaseClose == 0:
                MState = 0
        else:
                MState = Magnet
                
        
        OutputInstructions.append(EncodeInstruction(MState))
        
        ##################################################################
        ##################### Luces encender y apagar ####################
        ##################################################################
        LightOn  = buttons[PUSH_R_BUTTON]*100
        LightOff = buttons[PUSH_L_BUTTON]*100
                
        if LightOn == 0 and LightOff == 100:
                LState = 100
        elif LightOn == 100 and LightOff == 0:
                LState = 0
        else:
                LState = Light
                
        
        OutputInstructions.append(EncodeInstruction(LState))
        ##################################################################
        ################## Velocidad #################
        ##################################################################
        Vel1  = buttons[TRIANGLE_BUTTON]*100
        Vel2 = buttons[X_BUTTON]*100
                
        if Vel1 == 0 and Vel2 == 100:
                Velocidad = 100
        elif Vel1 == 100 and Vel2 == 0:
                Velocidad = 0
        else:
                Velocidad = Vel
                
        
        OutputInstructions.append(EncodeInstruction(Velocidad))
        ##################################################################
        
        return OutputInstructions, LState, MState, Velocidad

        
#-------------------------------------------------MAIN------------------------------------------------#  
def Main():
        LightState = 0
        MagnetState = 0
        Velocidad = 0

        connected = False

        while True:
                i = 0
                while not connected:
                        try:
                                i += 1
                                print str(i)
                                socketClient = socket.socket()
                                socketClient.connect((HOST, PORT))
                                connected = True
                        except socket.error:
                                print 'Intentando conectar...'
                        #except KeyboardInterrupt:
                        #        print 'Saliendo, adios'
                        #        return
                try:
                        axes, buttons = getPositions(gpad)
                        OutputInstructions, LightState, MagnetState, Velocidad = getInstructions(axes, buttons, LightState, MagnetState, Velocidad)
                        InstructionChain = ''.join(OutputInstructions)
                
                        print InstructionChain
                        socketClient.settimeout(0.5)
                        try:
                                socketClient.send(InstructionChain)
                        except socket.timeout:
                                socketClient.close()
                                connected = False
                        time.sleep(DELAY)

                except socket.error:
                        time.sleep(0.01)
                        print 'Se perdio la conexion, intentando reconectar...'
                        connected = False

                #except KeyboardInterrupt:
                #        socketClient.close()
                #        print "\nFinalizando programa..."
                #        break
        
#------------------------------------------------INICIO-----------------------------------------------#
gpad = getJoystick()
gpad.init()



if __name__ == '__main__':
        Main()
