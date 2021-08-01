import java.io.*;

public class Parser_3_2 {
	private Lexer_2_3 lex;
	private BufferedReader pbr;
	private Token look;

	public Parser_3_2(Lexer_2_3 l, BufferedReader br) {
		lex = l;
		pbr = br;
		move();
	}

	void move() {
		look = lex.lexical_scan(pbr);
		System.out.println("token = " + look);
	}

	void error(String s) {
		throw new Error("near line " + Lexer_2_3.line + ": " + s);
	}

	void match(int t) {
		if (look.tag == t) {
			if (look.tag != Tag.EOF)
				move();
		} else
			error("syntax error");
	}

	/*	Insieme Guida
	*  <prog>  		-> <stat> EOF						GUI{(}
	*  <statlist>  	-> <stat> <statlistp> 				GUI{(}
	*  <statlistp> 	-> <stat> <statlistp> 				GUI{(}
	*  		  		|  £				   				GUI{), EOF}
	*  <stat>  		-> ( <statp> )					GUI{(}
	*  <statp>  		-> = ID <expr>					GUI{=}
	*  		  		|  cond <bexpr> <stat> <elseopt> 	GUI{cond}
	*				|  while <bexpr> <stat>		 	GUI{while}
	*				|  do <statlist>  				GUI{do}
	*				|  print <exprlist> 			 	GUI{print}
	*				|  read	ID					 	GUI{read}
	*  <elseopt> 		-> (else <stat>) 					GUI{(}
	*				|  £								GUI{)}
	*  <bexpr> 		-> (<bexprp>) 					GUI{(}
	*  <bexprp> 		-> RELOP <expr> <expr> 			GUI{RELOP}
	*  <expr> 		-> NUM 							GUI{NUM}
	*				|  ID							GUI{ID}
	*				|  ( <exprp> )					GUI{(}
	*  <exprp> 		-> + <exprlist> 					GUI{+}
	*				|  - <expr> <expr>				GUI{-}
	*				|  *	<exprlist>					GUI{*}
	*				|  / <expr> <expr>				GUI{/}
	*  <exprlist> 	-> <expr> <exprlistp> 				GUI{NUM,ID,(}
	*  <exprlistp> 	-> <expr> <exprlistp> 				GUI{NUM,ID,(}
	*				|  £								GUI{)}
	*/

	public void prog() {
		if (look.tag == '(') { // GUI{(}
			stat();
			match(Tag.EOF);
		} else
			error("Error in prog");
	}

	public void statlist() {
		if (look.tag == '(') { // GUI{(}
			stat();
			statlistp();
		} else
			error("Error in statlist");
	}

	public void statlistp() {
		switch (look.tag) {
			case '(': // GUI{(}
				stat();
				statlistp();
				break;
			case ')': // GUI{)}
				break;
			default:
				error("Error in statlistp");
				break;
		}
	}

	public void stat() {
		if (look.tag == '(') { // GUI{(}
			match('(');
			statp();
			match(')');
		} else
			error("Error in statp");
	}

	public void statp() {
		switch (look.tag) {
			case '=': // GUI{=}
				match('=');
				match(Tag.ID);
				expr();
				break;
			case Tag.COND: // GUI{cond}
				match(Tag.COND);
				bexpr();
				stat();
				elseopt();
				break;
			case Tag.WHILE: // GUI{while}
				match(Tag.WHILE);
				bexpr();
				stat();
				break;
			case Tag.DO: // GUI{do}
				match(Tag.DO);
				statlist();
				break;
			case Tag.PRINT: // GUI{print}
				match(Tag.PRINT);
				exprlist();
				break;
			case Tag.READ: // GUI{read}
				match(Tag.READ);
				match(Tag.ID);
				break;
			default:
				error("Error in statp");
				break;
		}
	}

	public void elseopt() {
		switch (look.tag) {
			case '(': // GUI{(}
				match('(');
				match(Tag.ELSE);
				stat();
				match(')');
				break;
			case ')': // GUI{)}
				break;
			default:
				error("Error in elseopt");
				break;
		}
	}

	public void bexpr() {
		if (look.tag == '(') { // GUI{(}
			match('(');
			bexprp();
			match(')');
		} else
			error("Error in bexpr");
	}

	public void bexprp() {
		if (look.tag == Tag.RELOP) { // GUI{RELOP}
			match(Tag.RELOP);
			expr();
			expr();
		} else
			error("Error in bexprp");
	}

	public void expr() {
		switch (look.tag) {
			case Tag.NUM: // GUI{NUM}
				match(Tag.NUM);
				break;
			case Tag.ID: // GUI{ID}
				match(Tag.ID);
				break;
			case '(': // GUI{(}
				match('(');
				exprp();
				match(')');
				break;
			default:
				error("Error in expr");
				break;
		}
	}

	public void exprp() {
		switch (look.tag) {
			case '+': // GUI{+}
				match('+');
				exprlist();
				break;
			case '-': // GUI{-}
				match('-');
				expr();
				expr();
				break;
			case '*': // GUI{*}
				match('*');
				exprlist();
				break;
			case '/':
				match('/'); // GUI{/}
				expr();
				expr();
				break;
			default:
				error("Error in exprp");
				break;
		}
	}

	public void exprlist() {
		switch (look.tag) {
			case Tag.NUM:
			case Tag.ID:
			case '(': // GUI{NUM,ID,(}
				expr();
				exprlistp();
				break;
			default:
				error("Error in exprlist");
				break;
		}
	}

	public void exprlistp() {
		switch (look.tag) {
			case Tag.NUM:
			case Tag.ID:
			case '(': // GUI{NUM,ID,(}
				expr();
				exprlistp();
				break;
			case ')': // GUI{)}
				break;
			default:
				error("Error in exprlistp");
				break;
		}
	}

	public static void main(String[] args) {
		Lexer_2_3 lex = new Lexer_2_3();
		String path = "test/euclid.lft"; 
		try {
			BufferedReader br = new BufferedReader(new FileReader(path));
			Parser_3_2 parser = new Parser_3_2(lex, br);
			parser.prog();
			System.out.println("Input OK");
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
