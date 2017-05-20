public class ProcessingThread extends Thread{
    public int id;
    public byte b;
    public byte[] subarray;
    public Op threadOp;
    public int ret;

    @Override
    public void run(){
        try {
            subarray=threadOp.logb(subarray, b);
            //ret=threadOp.prod(subarray);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
