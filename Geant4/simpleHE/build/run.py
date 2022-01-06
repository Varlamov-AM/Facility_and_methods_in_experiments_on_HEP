
import os

angleMin = 45.0
angleMax = 60.0
nbins = 250
step = (angleMax - angleMin)/nbins

for i in range(nbins):
    currAngle = angleMin + i*step + step/2
    command = "./simpleHE.exe run.mac " + str(currAngle);
#    print(command)
    os.system(command)
    command = "mv Logic_test.root logic_test_"+str(currAngle) + ".root"
#    print(command)
    os.system(command)

