import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Op extends Remote{
    public byte[] logb (byte[] a, byte b) throws RemoteException;
    public byte[] power (byte[] a, byte b) throws RemoteException;
    public byte[] sine (byte[] a) throws RemoteException;
    public int sum (byte[] a) throws RemoteException;
    public int largerthan (byte[] a, byte b) throws RemoteException;
    public int prod (byte[] a) throws RemoteException;
}
