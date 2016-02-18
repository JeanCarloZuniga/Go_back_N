import re
file_user = input("Introduzca el nombre del archivo: ")
fileF = open(file_user, 'r')
contadorUnos = 0
contadorOtros = 0
total = 0
matcher = re.compile('0[^0-9]+')
for line in fileF:
	if(matcher.match(line)):
		contadorUnos += 1
	else:
		contadorOtros += 1

print('La cantidad de unos son: '+str(contadorUnos))
print('Los otros son: '+ str(contadorOtros))
fileF.close()

