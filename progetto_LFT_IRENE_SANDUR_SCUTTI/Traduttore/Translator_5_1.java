import java.io.*;

public class Translator_5_1 {
	private Lexer_2_3 lex;
	private BufferedReader pbr;
	private Token look;

	SymbolTable st = new SymbolTable();
	CodeGenerator code = new CodeGenerator();
	int count = 0;

	public Translator_5_1(Lexer_2_3 l, BufferedReader br) {
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

	public void prog() {
		if (look.tag == '(') {
			int lnext_prog = code.newLabel();
			code.emitLabel(lnext_prog);
			stat(lnext_prog);
			match(Tag.EOF);
			try {
				code.toJasmin();
			} catch (java.io.IOException e) {
				System.out.println("IO error\n");
			}
		} else
			error("Error in prog");
	}

	public void statlist(int lnext) {
		if (look.tag == '(') {
			stat(lnext);
			lnext = code.newLabel();
			code.emitLabel(lnext);
			statlistp(lnext);
		} else
			error("Error in statlist");
	}

	public void statlistp(int lnext) {
		// int lnext_statlistp = code.newLabel();
		switch (look.tag) {
			case '(':
				stat(lnext);
				lnext = code.newLabel();
				code.emitLabel(lnext);
				statlistp(lnext);
				break;
			case ')':
			case Tag.EOF:
				break;
			default:
				error("Error in statlistp");
		}
	}

	public void stat(int lnext) {
		if (look.tag == '(') {
			match('(');
			statp(lnext);
			match(')');
		} else {
			error("Error in stat");
		}
	}

	public void statp(int lnext) {
		int goto_label, true_label, false_label;
		switch (look.tag) {
			case '=':
				match('=');
				int assign_id_addr = st.lookupAddress(((Word) look).lexeme);
				if (look.tag == Tag.ID) {
					if (assign_id_addr == -1) {
						assign_id_addr = count;
						st.insert(((Word) look).lexeme, count++);
					}
				}
				match(Tag.ID);
				expr();
				code.emit(OpCode.istore, assign_id_addr);
				break;
			case Tag.COND:
				match(Tag.COND);
				true_label = code.newLabel();
				bexpr(true_label);
				false_label = code.newLabel();
				code.emit(OpCode.GOto, false_label);
				code.emit(OpCode.label, true_label);
				stat(true_label);
				goto_label = code.newLabel();
				code.emit(OpCode.GOto, goto_label);
				elseopt(false_label);
				code.emit(OpCode.label, goto_label);
				break;
			case Tag.WHILE:
				match(Tag.WHILE);
				int end = code.newLabel();
				int begin = lnext;
				true_label = code.newLabel();
				bexpr(true_label);
				code.emit(OpCode.GOto, end);
				code.emitLabel(true_label);
				stat(lnext);
				code.emit(OpCode.GOto, begin);
				code.emitLabel(end);
				break;
			case Tag.DO:
				match(Tag.DO);
				statlist(lnext);
				break;
			case Tag.PRINT:
				match(Tag.PRINT);
				int op_type = 2;
				exprlist(op_type);
				break;
			case Tag.READ:
				match(Tag.READ);
				if (look.tag == Tag.ID) {
					int read_id_addr = st.lookupAddress(((Word) look).lexeme);
					if (read_id_addr == -1) {
						read_id_addr = count;
						st.insert(((Word) look).lexeme, count++);
					}
					match(Tag.ID);
					code.emit(OpCode.invokestatic, 0);
					code.emit(OpCode.istore, read_id_addr);
					break;
				}
			default:
				error("Error in grammar (stat) after read with " + look);
				break;
		}
	}

	private void elseopt(int lnext) {
		switch (look.tag) {
			case '(':
				match('(');
				match(Tag.ELSE);
				code.emit(OpCode.label, lnext);
				stat(lnext);
				match(')');
				break;
			case ')':
				break;
			default:
				error("Error in elseopt");
				break;
		}
	}

	private void bexpr(int lnext) {
		if (look.tag == '(') {
			match('(');
			bexprp(lnext);
			match(')');
		} else {
			error("Error in bexpr");
		}
	}

	private void bexprp(int lnext) {
		if (look.tag == Tag.RELOP) {
			switch (((Word) look).lexeme) {
				case ">":
					match(Tag.RELOP);
					expr();
					expr();
					code.emit(OpCode.if_icmpgt, lnext);
					break;
				case "<":
					match(Tag.RELOP);
					expr();
					expr();
					code.emit(OpCode.if_icmplt, lnext);
					break;
				case ">=":
					match(Tag.RELOP);
					expr();
					expr();
					code.emit(OpCode.if_icmpge, lnext);
					break;
				case "<=":
					match(Tag.RELOP);
					expr();
					expr();
					code.emit(OpCode.if_icmple, lnext);
					break;
				case "==":
					match(Tag.RELOP);
					expr();
					expr();
					code.emit(OpCode.if_icmpeq, lnext);
					break;
				case "<>":
					match(Tag.RELOP);
					expr();
					expr();
					code.emit(OpCode.if_icmpne, lnext);
					break;
			}
		} else {
			error("Error in bexprp");
		}
	}

	private void expr() {
		switch (look.tag) {
			case Tag.NUM:
				int expr_val = Integer.parseInt(((NumberTok) look).lexeme);
				match(Tag.NUM);
				code.emit(OpCode.ldc, expr_val);
				break;
			case Tag.ID:
				int id_addr = st.lookupAddress(((Word) look).lexeme);
				match(Tag.ID);
				code.emit(OpCode.iload, id_addr);
				break;
			case '(':
				match('(');
				exprp();
				match(')');
				break;
			default:
				error("Error in expr");
		}
	}

	private void exprp() {
		switch (look.tag) {
			case '+':
				match('+');
				int op_type = 0;
				exprlist(op_type);
				break;
			case '-':
				match('-');
				expr();
				expr();
				code.emit(OpCode.isub);
				break;
			case '*':
				match('*');
				op_type = 1;
				exprlist(op_type);
				break;
			case '/':
				match('/');
				expr();
				expr();
				code.emit(OpCode.idiv);
				break;
			default:
				error("Error in exprp");
		}
	}

	private void exprlist(int op_type) {
		if (look.tag == Tag.NUM || look.tag == Tag.ID || look.tag == '(') {
			expr();
			if (op_type == 2) {
				code.emit(OpCode.invokestatic, 1);
			}
			exprlistp(op_type);
		} else
			error("Errore nell'exprlist");
	}

	private void exprlistp(int op_type) {
		switch (look.tag) {
			case Tag.NUM:
			case Tag.ID:
			case '(':
				expr();
				switch (op_type) {
					case 0: // add
						code.emit(OpCode.iadd);
						break;
					case 1: // mul
						code.emit(OpCode.imul);
						break;
					case 2: // print
						code.emit(OpCode.invokestatic, 1);
						break;
				}
				exprlistp(op_type);
				break;
			case ')':
				break;
			default:
				error("Error in exprlistp");
		}
	}

	public static void main(String[] args) {
		Lexer_2_3 lex = new Lexer_2_3();
		String path = "Test/max_tre_num.lft";
		try {
			BufferedReader br = new BufferedReader(new FileReader(path));
			Translator_5_1 translator = new Translator_5_1(lex, br);
			translator.prog();
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
