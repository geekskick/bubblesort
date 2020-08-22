package bubblesort;

public class BenchmarkRun {
	@Override
	public String toString() {
		return "BenchmarkRun [elements=" + elements + ", ns_taken=" + ns_taken + ", name=" + name + "]";
	}
	int elements;
	Double ns_taken;
	String name;
	
	public String getName() {
		return name;
	}
	public BenchmarkRun(String n, Double ns){
		name = n;
		elements = Integer.parseInt(n.split("/")[1]);
		ns_taken = ns;
	}
	public int getElements() {
		return elements;
	}
	public Double getNs_taken() {
		return ns_taken;
	}
}
