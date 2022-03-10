#!/bin/bash 

CONTADOR_OBJETOS=250
CONTADOR_ITERACIONES_SIMULACION=100
CONTADOR_ITERACIONES_EJECUCION_PROGRAMA=0
CONTADOR_HILOS=1

rm Tiempos*

while [ $CONTADOR_HILOS -le 16 ]
do
	export OMP_NUM_THREADS=${CONTADOR_HILOS}
	while [ $CONTADOR_OBJETOS -le 1000 ]
	do
			echo "----------------- Ejecución con ${CONTADOR_OBJETOS} objetos y ${CONTADOR_HILOS} hilos en AOS y SOA-----------------" 
			echo "----------------- Ejecución con ${CONTADOR_OBJETOS} objetos y ${CONTADOR_HILOS} hilos en AOS -----------------" >> Tiempos_aos_obj.txt
			echo "----------------- Ejecución con ${CONTADOR_OBJETOS} objetos y ${CONTADOR_HILOS} hilos en SOA -----------------" >> Tiempos_soa_obj.txt  
			echo "Objetos = ${CONTADOR_OBJETOS}. Iteraciones = ${CONTADOR_ITERACIONES_SIMULACION}. Hilos = ${CONTADOR_HILOS}. "
			echo "Objetos = ${CONTADOR_OBJETOS}. Iteraciones = ${CONTADOR_ITERACIONES_SIMULACION}. Hilos = ${CONTADOR_HILOS}. " >> Tiempos_aos_obj.txt
			echo "Objetos = ${CONTADOR_OBJETOS}. Iteraciones = ${CONTADOR_ITERACIONES_SIMULACION}. Hilos = ${CONTADOR_HILOS}. " >> Tiempos_soa_obj.txt
 		
				while [ $CONTADOR_ITERACIONES_EJECUCION_PROGRAMA -lt 10 ]
	  			do
			   		./../nbodyrnd aos ${CONTADOR_OBJETOS} ${CONTADOR_ITERACIONES_SIMULACION} | grep "Total" >> Tiempos_aos_obj.txt
					./../nbodyrnd soa ${CONTADOR_OBJETOS} ${CONTADOR_ITERACIONES_SIMULACION} | grep "Total" >> Tiempos_soa_obj.txt  
					let CONTADOR_ITERACIONES_EJECUCION_PROGRAMA+=1
				done
				CONTADOR_ITERACIONES_EJECUCION_PROGRAMA=0

				let CONTADOR_OBJETOS+=250 
	done
	let CONTADOR_HILOS=$((CONTADOR_HILOS*2))
	CONTADOR_OBJETOS=250
	CONTADOR_ITERACIONES_SIMULACION=100
	CONTADOR_ITERACIONES_EJECUCION_PROGRAMA=0
done
CONTADOR_OBJETOS=50
CONTADOR_ITERACIONES_SIMULACION=50
CONTADOR_ITERACIONES_PROGRAMA=0
CONTADOR_HILOS=1

while [ $CONTADOR_HILOS -le 16 ]
do
		export OMP_NUM_THREADS=${CONTADOR_HILOS}
		while [ $CONTADOR_ITERACIONES_SIMULACION -le 200 ]
		do
			echo "----------------- Ejecución con ${CONTADOR_OBJETOS} objetos y ${CONTADOR_HILOS} hilos en AOS y SOA-----------------" 
			echo "----------------- Ejecución con ${CONTADOR_OBJETOS} objetos y ${CONTADOR_HILOS} hilos en AOS -----------------" >> Tiempos_aos_ite.txt
			echo "----------------- Ejecución con ${CONTADOR_OBJETOS} objetos y ${CONTADOR_HILOS} hilos en SOA -----------------" >> Tiempos_soa_ite.txt  
			echo "Objetos = ${CONTADOR_OBJETOS}. Iteraciones = ${CONTADOR_ITERACIONES_SIMULACION}. Hilos = ${CONTADOR_HILOS}. "
			echo "Objetos = ${CONTADOR_OBJETOS}. Iteraciones = ${CONTADOR_ITERACIONES_SIMULACION}. Hilos = ${CONTADOR_HILOS}. " >> Tiempos_aos_ite.txt
			echo "Objetos = ${CONTADOR_OBJETOS}. Iteraciones = ${CONTADOR_ITERACIONES_SIMULACION}. Hilos = ${CONTADOR_HILOS}. " >> Tiempos_soa_ite.txt
 
				while [ $CONTADOR_ITERACIONES_EJECUCION_PROGRAMA -lt 10 ]
	   			do
			   		./../nbodyrnd aos ${CONTADOR_OBJETOS} ${CONTADOR_ITERACIONES_SIMULACION} | grep "Total" >> Tiempos_aos_ite.txt
					./../nbodyrnd soa ${CONTADOR_OBJETOS} ${CONTADOR_ITERACIONES_SIMULACION} | grep "Total" >> Tiempos_soa_ite.txt  
					let CONTADOR_ITERACIONES_EJECUCION_PROGRAMA+=1
				done
				CONTADOR_ITERACIONES_EJECUCION_PROGRAMA=0

				let CONTADOR_ITERACIONES_SIMULACION+=50 
		done
		let CONTADOR_HILOS=$((CONTADOR_HILOS*2))
		CONTADOR_OBJETOS=50
		CONTADOR_ITERACIONES_SIMULACION=50
		CONTADOR_ITERACIONES_PROGRAMA=0
done


