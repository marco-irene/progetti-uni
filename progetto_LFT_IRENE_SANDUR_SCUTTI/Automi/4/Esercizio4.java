public class Esercizio4{
	
	public static boolean scan(String s){
		int state = 0;
		int i = 0;
		
		
		while (state >= 0 && i < s.length()) {
	    	final char ch = s.charAt(i++);

	    	switch (state) {
				 case 0: 
					if (ch >= '0' && ch <= '9'){ 
					if ((int)ch%2 == 0)
						state = 1;
					else
						state = 2;
					}
					else 
						state = -1;
					break;
				
				case 1: 
					if (ch >= '0' && ch <= '9'){ 
					if ((int)ch%2 == 0)
						state = 1;
					else
						state = 2;
					} else if (ch == ' ')
						state = 6; 
					else if (ch >= 'A' && ch <= 'K')
						state = 3;
					
					else
						state = -1;
					break;
					
				case 2:
					if (ch >= '0' && ch <= '9'){ 
					if ((int)ch%2 == 0)
						state = 1;
					else 
						state = 2;
					} else if (ch == ' ')
						state = 5; 
					else if (ch >= 'L' && ch <= 'Z')
						state = 4;
					else
						state = -1;
					break;
					
				case 3:
					if ( ch >= 'a' && ch <= 'z')
						state = 3;
					else if (ch == ' ')
						state = 7;
					else
						state = -1;
					break;
				
				case 4:
					if ( ch >= 'a' && ch <= 'z')
						state = 4;
					else if( ch == ' ')
						state = 7;
					else
						state = -1;
				
				case 5:
					if (ch >= 'L' && ch <= 'Z' )
						state = 4;
					else 
						state = -1;
					
				case 6:
					if (ch >= 'A' && ch <= 'K' )
						state = 3;
					else 
						state = -1;	
				
				case 7:
					if (ch >= 'L' && ch <= 'Z' )
						state = 4;
					else if (ch >= 'A' && ch <= 'K' )
						state = 3;
					else 
						state = -1;
					
			}
			
		}
		 if(state == 3 || state == 4 || state == 7)
			return true;
		else 
			return false;
	}
				
					
	public static void main(String[] args) {
	System.out.println(scan(args[0]) ? "OK" : "NOPE");
    }
}