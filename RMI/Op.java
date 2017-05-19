import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Op extends Remote{
    public byte[] logb (byte[] a, byte b) throws RemoteException;
    public byte[] power (byte[] a, byte b) throws RemoteException;
    public byte[] sine (byte[] a) throws RemoteException;
    public byte sum (byte[] a) throws RemoteException;
    public byte largerthan (byte[] a, byte b) throws RemoteException;
    public byte prod (byte[] a) throws RemoteException;
}
