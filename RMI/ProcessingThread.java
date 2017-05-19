public class ProcessingThread extends Thread{
    public int id;
    public byte b;
    public byte[] subarray;
    public Op threadOp;

    @Override
    public void run(){
        try {
            subarray=threadOp.logb(subarray, b);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
