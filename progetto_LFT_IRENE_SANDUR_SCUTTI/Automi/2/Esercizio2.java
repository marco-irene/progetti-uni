public class Esercizio2 {
	
	public static boolean scan(String s){
		int state = 0;
		int i = 0;
		
		if (s != null){
		while (state >= 0 && i < s.length()) {
	    	final char ch = s.charAt(i++);

	    	switch (state) {
				case 0: 
					if (ch >= '0' && ch <= '9') 
						state = -1; 
					else if (ch == '_')
						state = 1;
					else if( ch >= 'a' && ch <= 'z')
						state = 2;
					else 
						state = -1;
					break;
				
				case 1:
					if (ch == '_')
						state = 1;
					else if ( ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9')
						state = 2;
					else 
						state = -1;
					break;
					
				case 2:
					if ( ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch == '_')
						state = 2;
					else 
						state = -1;
					break;
			}
			
		}
		}else state = 2;
		return state == 2;
	}
				
					
	public static void main(String[] args) {
	System.out.println(scan(args[0]) ? "così va bene" : "proprio no");
    }
}
					