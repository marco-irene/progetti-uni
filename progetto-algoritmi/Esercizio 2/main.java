 public static void main(String[] args) {
        String s1 = "cassa";
        String s2 = "casa";
        System.out.println(EditDistance.edit_distance(s1, s2, 0, 0));
        System.out.println(EditDistance.edit_distance(s1, s2));
}