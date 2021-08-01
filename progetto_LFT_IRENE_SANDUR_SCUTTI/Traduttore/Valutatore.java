import java.io.*;

public class Valutatore {
	private Lexer_2_3 lex;
	private BufferedReader pbr;
	private Token look;

	public Valutatore(Lexer_2_3 l, BufferedReader br) {
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

	public void start() {
		int expr_val;
		if (look.tag == '(' || look.tag == Tag.NUM) {
			expr_val = expr();
			match(Tag.EOF);
		} else {
			expr_val = 0;
			error("Error in start");
		}
		System.out.println(expr_val);
	}

	private int expr() {
		int term_val, exprp_val;
		if (look.tag == '(' || look.tag == Tag.NUM) {
			term_val = term();
			exprp_val = exprp(term_val);
		} else {
			exprp_val = 0;
			error("Error in expr");
		}
		return exprp_val;
	}

	private int exprp(int exprp_i) {
		int term_val, exprp_val;
		switch (look.tag) {
			case '+':
				match('+');
				term_val = term();
				exprp_val = exprp(exprp_i + term_val);
				return exprp_val;
			case '-':
				match('-');
				term_val = term();
				exprp_val = exprp(exprp_i - term_val);
				return exprp_val;
			case ')':
			case Tag.EOF:
				return exprp_i;
			default:
				error("Error in exprp");
				return 0;
		}
	}

	private int term() {
		int fact_val, termp_val;
		if (look.tag == '(' || look.tag == Tag.NUM) {
			fact_val = fact();
			termp_val = termp(fact_val);
		} else {
			termp_val = 0;
			error("Error in term");
		}
		return termp_val;
	}

	private int termp(int termp_i) {
		int termp_val, fact_val;
		switch (look.tag) {
			case '*':
				match('*');
				fact_val = fact();
				termp_val = termp(termp_i * fact_val);
				return termp_val;
			case '/':
				match('/');
				fact_val = fact();
				termp_val = termp(termp_i / fact_val);
				return termp_val;
			case '+':
			case '-':
			case ')':
			case Tag.EOF:
				return termp_i;
			default:
				error("Error in termp");
				return 0;
		}
	}

	private int fact() {
		int fact_val;
		switch (look.tag) {
			case '(':
				match('(');
				fact_val = expr();
				match(')');
				return fact_val;
			case Tag.NUM:
				fact_val = Integer.parseInt(((NumberTok) look).lexeme);
				match(look.tag);
				return fact_val;
			default:
				error("Error in fact");
				return 0;
		}
	}

	public static void main(String[] args) {
		Lexer_2_3 lex = new Lexer_2_3();
		String path = "Test/TestParser1.txt"; // il percorso del file da leggere
		try {
			BufferedReader br = new BufferedReader(new FileReader(path));
			Valutatore valutatore = new Valutatore(lex, br);
			valutatore.start();
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}