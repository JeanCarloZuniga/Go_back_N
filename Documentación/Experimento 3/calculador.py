file_user = input("Introduzca el nombre del archivo: ")
fileF = open(file_user, 'r')
contador = 0
total = 0
for line in fileF:
	number = int(line)
	total += number
	contador += 1
	
promedio = total/contador
print(str(promedio))
fileF.close()
