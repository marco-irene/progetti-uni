import java.io.*;

public class Parser_3_1 {
	private Lexer_2_3 lex;
	private BufferedReader pbr;
	private Token look;

	public Parser_3_1(Lexer_2_3 l, BufferedReader br) {
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

	/* <start> -> <expr> EOF		GUI{(,NUM}
	*  <expr>  -> <term> <exprp> 	GUI{(,NUM}
	*  <exprp> -> +<term> <exprp> 	GUI{+}
	*  		  |  -<term> <exprp>   GUI{-}
	*  		  |  £				GUI{), EOF}
	*  <term>  -> <fact> <termp>	GUI{(,NUM}
	*  <termp> -> *<fact> <termp>	GUI{*}
	*  		  |  /<fact> <termp> 	GUI{/}
	*		  | £				GUI{EOF,),+,-}
	*  <fact>  -> (<expr>)			GUI{(}
	*  <fact>  -> NUM				GUI{NUM}
	*/

	public void start() { // GUI {(,NUM}
		if (look.tag == '(' || look.tag == Tag.NUM) {
			expr();
			match(Tag.EOF);
		} else
			error("Error in start");
	}

	private void expr() { // GUI {(,NUM}
		if (look.tag == '(' || look.tag == Tag.NUM) {
			term();
			exprp();
		} else
			error("Error in expr");
	}

	private void exprp() {
		switch (look.tag) {
			case '+':// GUI{+}
				match('+');
				term();
				exprp();
				break;
			case '-':// GUI{-}
				match('-');
				term();
				exprp();
				break;
			case ')':// GUI{)}
			case Tag.EOF: // GUI{EOF}
				break;
			default:
				error("Error in exprp");
		}
	}

	private void term() {
		if (look.tag == '(' || look.tag == Tag.NUM) { // GUI{(,NUM}
			fact();
			termp();
		} else
			error("Error in term");
	}

	private void termp() {
		switch (look.tag) {
			case ('*'): // GUI{*}
				match('*');
				fact();
				termp();
				break;
			case ('/'): // GUI{/}
				match('/');
				fact();
				termp();
				break;
			case ('+'): // GUI{+}
			case ('-'): // GUI{-}
			case (')'): // GUI{)}
			case (Tag.EOF): // GUI{EOF}
				break;
			default:
				error("Error in termp");
		}
	}

	private void fact() {
		if (look.tag == '(') { // GUI{(}
			match('(');
			expr();
			match(')');
		} else if (look.tag == Tag.NUM) { // GUI{NUM}
			match(Tag.NUM);
		} else
			error("Error in fact :");
	}

	public static void main(String[] args) {
		Lexer_2_3 lex = new Lexer_2_3();
		String path = "Test/TestParser1.txt";
		try {
			BufferedReader br = new BufferedReader(new FileReader(path));
			Parser_3_1 parser = new Parser_3_1(lex, br);
			parser.start();
			System.out.println("Input OK");
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}