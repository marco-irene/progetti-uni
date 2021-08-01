import java.io.*;

public class Lexer_2_3 {

	public static int line = 1;
	private char peek = ' ';

	private void readch(BufferedReader br) {
		try {
			peek = (char) br.read();
		} catch (IOException exc) {
			peek = (char) -1; // ERROR
		}
	}

	public Token lexical_scan(BufferedReader br) {
		while (peek == ' ' || peek == '\t' || peek == '\n' || peek == '\r') {
			if (peek == '\n')
				line++;
			readch(br);
		}

		switch (peek) {
			// ... gestire i casi di (, ), {, }, +, -, *, /, ; ... //
			case '!':
				peek = ' ';
				return Token.not;
			case ')':
				peek = ' ';
				return Token.rpt;
			case '(':
				peek = ' ';
				return Token.lpt;
			case '{':
				peek = ' ';
				return Token.lpg;
			case '}':
				peek = ' ';
				return Token.rpg;
			case '+':
				peek = ' ';
				return Token.plus;
			case '-':
				peek = ' ';
				return Token.minus;
			case '*':
				peek = ' ';
				return Token.mult;
			case '/':
				readch(br);
				if (peek == '/') { // commento con doppio slash
					while (peek != '\n' && peek != (char) -1) {
						readch(br);
					}
					return lexical_scan(br);
				} else if (peek == '*') { // commento con slash asterisco
					boolean found = false;
					while (found == false && peek != (char) -1) {
						readch(br);
						while (peek == '*') {
							readch(br);
							if (peek == '/')
								found = true;
						}
					}
					if (found == true) { // verifica che il commento si chiuda
						peek = ' ';
						return lexical_scan(br);
					} else {
						System.err.println("File ended while commenting");
						return new Token(Tag.EOF);
					}
				} else
					peek = ' ';
				return Token.div;
			// ... gestire i casi di ||, <, >, <=, >=, ==, <>, = ... //
			case '&':
				readch(br);
				if (peek == '&') {
					peek = ' ';
					return Word.and;
				} else {
					System.err.println("Erroneous character" + " after & : " + peek);
					return null;
				}
			case '|':
				readch(br);
				if (peek == '|') {
					peek = ' ';
					return Word.or;
				} else {
					System.out.println("Erroneus Character" + " after | : " + peek);
					return null;
				}
			case '<':
				readch(br);
				if (peek == ' ') {
					peek = ' ';
					return Word.lt;
				} else if (peek == '=') {
					peek = ' ';
					return Word.le;
				} else if (peek == '>') {
					peek = ' ';
					return Word.ne;
				} else {
					System.out.println("Erroneus Character" + " after < : " + peek);
					return null;
				}
			case '>':
				readch(br);
				if (peek == ' ') {
					peek = ' ';
					return Word.gt;
				} else if (peek == '=') {
					peek = ' ';
					return Word.ge;
				} else {
					System.out.println("Erroneus Character" + " after > : " + peek);
					return null;
				}
			case '=':
				readch(br);
				if (peek == '=') {
					peek = ' ';
					return Word.eq;
				} else {
					return Token.assign;
				}
			case ';':
				peek = ' ';
				return Token.semicolon;
			case (char) -1:
				return new Token(Tag.EOF);
			default:
				if (Character.isLetter(peek) || peek == '_') {
					// ... gestire il caso degli identificatori e delle parole chiave //
					String s = "";
					do {
						s += peek;
						readch(br);
					} while (Character.isLetterOrDigit(peek) || peek == '_');
					switch (s) {
						case "cond":
							return Word.cond;
						case "when":
							return Word.when;
						case "then":
							return Word.then;
						case "else":
							return Word.elsetok;
						case "while":
							return Word.whiletok;
						case "do":
							return Word.dotok;
						case "seq":
							return Word.seq;
						case "print":
							return Word.print;
						case "read":
							return Word.read;
						case "_":
							System.err.println("Erroneous character: " + peek);
							return null;
						default:
							return new Word(Tag.ID, s);
					}
				} else if (Character.isDigit(peek)) {
					// ... gestire il caso dei numeri ... //
					int x = (peek - 48);
					readch(br);
					while (Character.isDigit(peek)) {
						x = x * 10 + (peek - 48);
						readch(br);
					}
					if (Character.isLetter(peek) == false) {
						return NumberTok.num(x);
					} else {
						System.err.println("Erroneous character: " + peek);
						return null;
					}
				} else {
					System.err.println("Erroneous character: " + peek);
					return null;
				}
		}
	}

	public static void main(String[] args) {
		Lexer_2_3 lex = new Lexer_2_3();
		String path = "Test/TestLexer.txt"; // il percorso del file da leggere
		try {
			BufferedReader br = new BufferedReader(new FileReader(path));
			Token tok;
			do {
				tok = lex.lexical_scan(br);
				System.out.println("Scan: " + tok);
			} while (tok.tag != Tag.EOF);
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
