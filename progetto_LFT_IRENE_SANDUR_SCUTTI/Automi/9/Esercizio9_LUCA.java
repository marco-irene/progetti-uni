public class Esercizio9_LUCA {
	
	public static boolean scan(String s){
		int state = 0;
		int i = 0;
		
		
		while (state >= 0 && i < s.length()) {
	    	final char ch = s.charAt(i++);

	    	switch (state) {
				case 0: 
					if (ch == 'l' || ch == 'L') 
						state = 1; 
					else 
						state = 5;						
					break;
				
				case 1:
					 if ( ch =='u' || ch == 'U')
						state = 2;
					else 
						state = 6;
					break;
					
				case 2:
					  if ( ch == 'c' || ch == 'C')
						state = 3;
					else
						state = 7;
					break;
					
				case 3:
					state = 4;
					break;

				case 4:
					state = -1;	
					break;

				case 5:
					 if ( ch =='u' || ch == 'U')
						state = 6;
					else 
						state = -1;
					break;
					
				case 6:
					  if ( ch == 'c' || ch == 'C')
						state = 7;
					else
						state = -1;
					break;
				
				case 7:
					if (ch == 'a' || ch == 'A')
						state = 4;
					else 
						state = -1;
					break;
			}
		}
		return state == 4;
	}
								
	public static void main(String[] args) {
	System.out.println(scan(args[0]) ? "OK" : "NOPE");
    }
}