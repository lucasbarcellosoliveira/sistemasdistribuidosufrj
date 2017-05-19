import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.util.Arrays;

public class OpImplementation extends UnicastRemoteObject implements Op{
    OpImplementation() throws RemoteException{}

    @Override
    public byte[] logb(byte[] a, byte b) throws RemoteException{
        //System.out.println("Operation logb called for array "+Arrays.toString(a)+" and base "+b);
        for (int i=0;i<a.length;i++)
            a[i]=(byte) (Math.log(a[i])/Math.log(b));
        //System.out.println("Operation completed. Returning array "+Arrays.toString(a));
        return a;
    }

    @Override
    public byte[] power(byte[] a, byte b) throws RemoteException {
        //System.out.println("Operation power called for array "+Arrays.toString(a)+" and expoent "+b);
        for (int i=0;i<a.length;i++)
            a[i]=(byte) Math.pow(a[i],b);
        //System.out.println("Operation completed. Returning array "+Arrays.toString(a));
        return a;
    }

    @Override
    public byte[] sine(byte[] a) throws RemoteException {
        //System.out.println("Operation sine called for array "+Arrays.toString(a));
        for (int i=0;i<a.length;i++)
            a[i]=(byte) Math.sin(a[i]);
        //System.out.println("Operation completed. Returning array "+Arrays.toString(a));
        return a;
    }

    @Override
    public byte sum(byte[] a) throws RemoteException {
        //System.out.println("Operation sum called for array "+Arrays.toString(a));
        byte ret=0;
        for (int i=0;i<a.length;i++)
            ret+=a[i];
        //System.out.println("Operation completed. Returning value "+ret);
        return ret;
    }

    @Override
    public byte largerthan(byte[] a, byte b) throws RemoteException {
        //System.out.println("Operation largerthan called for array "+Arrays.toString(a)+" and value "+b);
        byte ret=0;
        for (int i=0;i<a.length;i++)
            if (a[i]>b)
                ret+=a[i];
        //System.out.println("Operation completed. Returning value "+ret);
        return ret;
    }

    @Override
    public byte prod(byte[] a) throws RemoteException {
        //System.out.println("Operation prod called for array "+Arrays.toString(a));
        byte ret=1;
        for (int i=0;i<a.length;i++)
            ret*=a[i];
        //System.out.println("Operation completed. Returning value "+ret);
        return ret;
    }
    
}
