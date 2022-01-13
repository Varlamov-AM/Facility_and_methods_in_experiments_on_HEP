import os

angleMin = 0.0
angleMax = 90.0
nbins = 90
step = (angleMax - angleMin)/nbins
dist = 300

for i in range(nbins):
    currAngle = angleMin + i*step + step/2
    command = "./../simpleHE.exe ../run.mac " + str(currAngle) + " " + str(dist) 
    print(command)
    os.system(command)
    command = "mv Angle_test.root Angle_test_" + str(currAngle) + "_" + str(dist) + "cm" + ".root"
#    print(command)
    os.system(command)
command = "hadd Final_angle_distribution_for_" + str(dist) + ".root" "Angle_test_*"
os.system(command)
