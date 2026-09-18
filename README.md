Desarrollo estructurado como un módulo de facilidades (FM) personalizado para Oracle BRM, 
implementando el opcode TPL_OP_BUSQUEDA_CUENTAS (25015). Este componente actúa como una capa de validación directa.   

Entrada de Datos: Recibe un flist de entrada que contiene el POID de ruteo y el número de cuenta específico a validar 
(PIN_FLD_ACCOUNT_NO).   

Lógica de Búsqueda: Prepara y ejecuta un PCM_OP_SEARCH dirigido a la clase /account utilizando 
el template "select X from /account where F1 = V1 ".   

Manejo de Resultados: Evalúa el conteo de elementos devueltos en el arreglo PIN_FLD_RESULTS.   
Salida: Construye un flist de retorno que inyecta la cadena "Cuenta Existe " si el número de cuenta fue localizado, o 
"Cuenta No Existe " en caso contrario, asignándolo al campo PIN_FLD_DESCR.
