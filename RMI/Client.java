import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

public class Client {
    public static void main(String args[]) throws NotBoundException, MalformedURLException, RemoteException, InterruptedException{

        int N=100000000;
        int K=64;
        byte[] array=new byte[N];//={1,2,3,4};
        byte b=2; //b=50;
        int ret=0;

        System.out.println("Starting client...");
        Op op=(Op) Naming.lookup("rmi://127.0.0.1:5000/VectorOperations");
        System.out.println("Client started!");
        ProcessingThread[] threads=new ProcessingThread[K];
        int i;
        for (i=0;i<N;i++)
            array[i]=(byte) ThreadLocalRandom.current().nextInt(1,100);
        //System.out.println("Sending array "+Arrays.toString(array));
        for (i=0;i<K;i++){
            threads[i]=new ProcessingThread();
            threads[i].id=i;
            threads[i].b=b;	
            threads[i].subarray=Arrays.copyOfRange(array, i*(N/K), i*(N/K)+(N/K));
            threads[i].threadOp=op;
        }
        long start, finish;
        start=System.nanoTime();
         for (i=0;i<K;i++)
            threads[i].start();
        for (i=0;i<K;i++)
            threads[i].join();
        //array=op.logb(array, b);
        finish=System.nanoTime();
        //System.out.println("Received array: "+Arrays.toString(array));
        System.out.println("Time elapsed (ns): "+(finish-start));

	//Printing type-1 functions
        //byte[] ansArray=new byte[N];
        //for (i=0;i<K;i++)
        //  System.arraycopy(threads[i].subarray, 0, ansArray, i*N/K, N/K);
        //System.out.println(Arrays.toString(ansArray));

	//Printing type-2 functions
	//for (i=0;i<K;i++)
	//  ret+=threads[i].ret;
	//System.out.println(ret);
    }
}
