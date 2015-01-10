import java.util.*;

public class ProducerConsumer {
    public class BoundedBuffer {
        public BoundedBuffer( ) {
            count = 0;
            in = 0;
            out = 0;
            buffer = new Object[BUFFER_SIZE];
        }
        public synchronized void enter( Object item ) {
            while ( count == BUFFER_SIZE ) {
                try  {
                    wait();
                } catch (Exception e) {
                    System.err.println("enter: wait() failed! " + e);
                }
            }
            
            ++count;
            buffer[in] = item;
            in = ( in + 1 ) % BUFFER_SIZE;
            notify();
        }
        public synchronized Object remove( ) { 
            Object item;
            while ( count == 0 ) {
                try  {
                    wait();
                } catch (Exception e) {
                    System.err.println("enter: wait() failed! " + e);
                }
            }
            --count;
            item = buffer[out];
            out = ( out + 1 ) % BUFFER_SIZE;
            notify();
            return item;
        }
        public static final int BUFFER_SIZE = 5;
        private int count;
        private int in;
        private int out;
        private Object[] buffer;
    }

    public class Producer extends Thread {
        BoundedBuffer boundedbuffer;
        Producer( BoundedBuffer b ) {
            boundedbuffer = b;
        }
        public void run( ) {
            for ( int i = 0; i < 5; i++ ) {
                boundedbuffer.enter( new Integer( i ) );
            }
			
		
                    suspend();
                
			
			
				
        } 
    }

    public class Consumer extends Thread {
        BoundedBuffer boundedbuffer;
        Consumer( BoundedBuffer b ) {
            boundedbuffer = b;
        }
        public void run( ) {
            int value = 0;
			while (value >= 0) {
				value = ( Integer )boundedbuffer.remove( );
                System.out.println( value );
				
            }
        }
    }

    ProducerConsumer( ) {
        BoundedBuffer b = new BoundedBuffer( );
        Producer producer = new Producer( b );
        Consumer consumer = new Consumer( b );
        producer.start( );
        consumer.start( );
    }
    
    public static void main( String[] args ) {
        ProducerConsumer procon = new ProducerConsumer( );
    }
}

