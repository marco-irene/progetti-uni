import java.util.concurrent.TimeUnit;

public class Chrono {
    private long elapsed_time;
    private long started_at;
    private boolean running;

    public Chrono() {
        reset();
    }

    public void reset() {
        synchronized (this) {
            elapsed_time = 0;
            running = false;
        }
    }

    public void start() {
        synchronized (this) {
            started_at = System.currentTimeMillis();
            running = true;
        }
    }

    public void stop() {
        synchronized (this) {
            elapsed_time += System.currentTimeMillis() - started_at;
            running = false;
        }
    }

    public long read() {
        synchronized (this) {
            return running ? elapsed_time + System.currentTimeMillis() : elapsed_time;
        }
    }

    public String toString() {

        return TimeUnit.MILLISECONDS.toSeconds(read()) + " seconds";
    }

}
