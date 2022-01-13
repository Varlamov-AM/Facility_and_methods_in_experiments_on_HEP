import os

angleMin = 0.0
angleMax = 90.0
nbins = 90
step = (angleMax - angleMin)/nbins

for i in range(nbins):
    currAngle = angleMin + i*step + step/2
    command = "./simpleHE.exe run.mac " + str(currAngle);
#    print(command)
    os.system(command)
    command = "mv Angle_test.root Angle_test_"+str(currAngle) + ".root"
#    print(command)
    os.system(command)

