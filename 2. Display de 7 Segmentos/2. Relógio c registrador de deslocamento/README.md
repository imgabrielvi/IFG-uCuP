Entrega dia 24/09.

1.Cadastro de usuário (10 usuários):

		i. ID numérico 4 dígitos;
		ii. Senha numérica de 4 dígitos.
	
2. Validação de usuário: 

		i. acesso ->	- Solenoide 12V;
				- Led [VM/VD].
			
3. Usar LCD e teclado numérico p/ apoio (interface).

		=========================================================
		TECLADO NUMÉRICO:
			[C5] B0 e [L4] B2 verificam '*';
			[C4] B1 e [L4] B2 verificam '#';
	
			Linhas:
				[L0] B6 aciona linha de '1', '2' e '3';
				[L1] B8 aciona linha de '4', '5' e '6';
				[L2] B9 aciona linha de '7', '8' e '9';
				[L3] B3 aciona linha de '0'.
	
			Colunas:
				[C0] B5 aciona coluna de '1', '4' e '7';
				[C1] B7 aciona coluna de '2' e '5';
				[C2] B10 aciona coluna de '3', '6' e '9';
				[C3] B4 aciona coluna de '8' e '0'.
		=========================================================

4.Matriz

		[C4][L4]	[C3][L3]	[C5][L4]
		
		[C2][L2]	[C3][L2]	[C0][L2]
		
		[C2][L1]	[C1][L1]	[C0][L1]
		
		[C2][L0]	[C1][L0]	[C0][L0]
