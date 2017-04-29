import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Op extends Remote{
    public float[] logb (float[] a, float b) throws RemoteException;
    public float[] power (float[] a, float b) throws RemoteException;
    public float[] sine (float[] a) throws RemoteException;
    public float sum (float[] a) throws RemoteException;
    public float largerthan (float[] a, float b) throws RemoteException;
    public float prod (float[] a) throws RemoteException;
}
