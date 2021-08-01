public class Esercizio5{
	
	public static boolean scan(String s){
		int state = 0;
		int i = 0;
		
		
		while (state >= 0 && i < s.length()) {
	    	final char ch = s.charAt(i++);

	    	switch (state) {
				case 0: 
					if (ch >= 'A' && ch <= 'K' || ch >= 'a' && ch <= 'k' ) 
						state = 1; 
					else if( ch >= 'l' && ch <= 'z' || ch >= 'L' && ch <= 'Z')
						state = 2;
					else 
						state = -1;
					break;
				
				case 1:								//a-k
					 if ( ch >= 'a' && ch <= 'z')				
						state = 1;
					else if(ch >= '0' && ch<= '9' &&  (int)ch%2 == 0) 
						state = 3;
					else if (ch >= '0' && ch<= '9' &&  (int)ch%2 == 1)
						state = 4;
					else
						state = -1;
					break;
					
				case 2:								//l-z
					  if ( ch >= 'a' && ch <= 'z')
						state = 2;
					else if(ch >= '0' && ch<= '9' &&  (int)ch%2 == 0) 
						state = 6;
					else if (ch >= '0' && ch<= '9' &&  (int)ch%2 == 1)
						state = 5;
					else
						state = -1;
					break;
				
				case 3:								//ak pari
					if (ch >= '0' && ch <= '9' && (int)ch%2== 1)
						state = 4;
					else if(ch >= '0' && ch <= '9' && (int)ch%2== 0)
						state = 3;
					else 
						state = -1;
					break;
					
				case 4:								//ak dispari
					if(ch >= '0' && ch <= '9' && (int)ch%2== 1)
						state = 4;
					else if (ch >= '0' && ch <= '9' && (int)ch%2== 0)
						state = 3;
					else
						state = -1;
					break;
					
				case 5:								//lz dispari
					if(ch >= '0' && ch <= '9' && (int)ch%2== 1)
						state = 5;
					else if(ch >= '0' && ch <= '9' && (int)ch%2== 0)
						state = 6;
					else 
						state = -1;
					break;
					
				case 6:								//lz pari
					if(ch >= '0' && ch <= '9' && (int)ch%2== 1)
						state = 5;
					else if (ch >= '0' && ch <= '9' && (int)ch%2== 0)
						state = 6;
					else
						state = -1;
					break;
			}
		}
		return state == 3 || state == 5;
	}
				
					
	public static void main(String[] args) {
	System.out.println(scan(args[0]) ? "OK" : "NOPE");
    }
}