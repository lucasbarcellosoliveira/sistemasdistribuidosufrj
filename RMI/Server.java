import java.net.MalformedURLException;
import java.rmi.AlreadyBoundException;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {
    public static void main(String args[]) throws RemoteException, AlreadyBoundException, MalformedURLException{
        System.out.println("Starting server...");
        System.setProperty("java.rmi.server.hostname", "127.0.0.1");
        LocateRegistry.createRegistry(5000);
        Op op=(Op) new OpImplementation();
        Naming.bind("rmi://127.0.0.1:5000/VectorOperations", (Remote) op);
        System.out.println("Server started!");
    }
}
