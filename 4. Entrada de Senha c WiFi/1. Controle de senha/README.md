Entrega dia 24/09.

1. Cadastro de usuário (10 usuários):
		
		 i. ID numérico 4 dígitos;
		ii. Senha numérica de 4 dígitos.
	
2. Validação de usuário: 

		i. acesso ->	- Solenoide 12V;
				- Led [VM/VD].
			
3. Usar LCD e teclado numérico p/ apoio (interface).

		=========================================================
		TECLADO NUMÉRICO:
			
			Linhas:
				[L0] B6 aciona linha de '#', '0' e '*';
				[L1] B8 aciona linha de '9', '8' e '7';
				[L2] B9 aciona linha de '6', '5' e '4';
				[L3] B3 aciona linha de '2';
				[L4] B2 aciona linha de '3' e '1'.
	
			Colunas:
				[C0] B5  aciona coluna de '#', '9' e '6';
				[C1] B7  aciona coluna de '0' e '8';
				[C2] B10 aciona coluna de '*', '7' e '4';
				[C3] B4  aciona coluna de '5' e '2';
				[C4] B1  aciona coluna de '1';
				[C5] B0  aciona coluna de '3';
		=========================================================


4.Matriz

		[C4][L4] = {1}	[C3][L3] = {2}	[C5][L4] = {3}
		
		[C2][L2] = {4}	[C3][L2] = {5}	[C0][L2] = {6}
		
		[C2][L1] = {7}	[C1][L1] = {8}	[C0][L1] = {9}
		
		[C2][L0] = {*}	[C1][L0] = {0}	[C0][L0] = {#}
