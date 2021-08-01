import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import static org.junit.Assert.assertEquals;


public class UnitTest {
    @Test
    public void testEditDistance(){

        assertEquals(0,EditDistanceFun.edit_distance("tassa","tassa"));
        assertEquals(4,EditDistanceFun.edit_distance("tassa","passato"));
    }

    @Test
    public void testEdiDistanceDyn(){
        assertEquals(4,EditDistanceFun.edit_distance_dyn("tassa","passato"));
        assertEquals(0,EditDistanceFun.edit_distance_dyn("passato","passato"));
    }

    @Test
    public void testCustomEdit(){
        assertEquals(2, EditDistanceFun.customEdit("vinaio", "vino"));
        assertEquals(0, EditDistanceFun.customEdit("pioppo", "pioppo"));

    }


}